import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

from datetime import datetime

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # 查询当前余额
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
    total = cash

    # 遍历每条股票, 查询最新价格（因为股票价格实时变化）, 并计算最新总资产
    rows = db.execute("SELECT * FROM holding_stock WHERE userid = ?", session["user_id"])
    for row in rows:
        # 查询最新价格（因为股票价格实时变化）
        current_price = lookup(row["symbol"])["price"]
        current_total = row["shares"] * current_price

        # 追加键值对
        row["price"] = current_price
        row["row_total"] = current_total

        # 实时计算最新总资产
        total = total + current_price * row["shares"]

    print(rows)

    return render_template("index.html", rows=rows, cash=cash, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        # 检查输入 symbol
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide symbol", 400)
        if not lookup(symbol):
            return apology("symbol is inexistence", 400)

        # 检查输入 shares
        shares = request.form.get("shares")
        if not shares:
            return apology("shares is empty", 400)
        if not shares.isdigit():
            return apology("shares should be a numberic", 400)
        shares = float(shares)
        if not shares > 0 or not shares.is_integer():
            return apology("shares should be a positive integer", 400)

        # 检查是否买得起
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
        print(cash)
        price = lookup(symbol)["price"]
        cost = price * shares
        if cost > cash:
            return apology("The balance is insufficient", 400)
        else:
            # 以下应该为一个事务, 否则会出现问题

            # 更新持有股票, 若有该股则增加持有量, 否则插入新纪录
            holding_shares = db.execute("SELECT shares FROM holding_stock WHERE userid = ? AND symbol = ?", session["user_id"], symbol)
            if holding_shares:
                holding_shares = holding_shares[0]["shares"]
                db.execute("UPDATE holding_stock SET shares = ? WHERE userid = ? AND symbol = ?", holding_shares + shares, session["user_id"], symbol)
            else:
                db.execute("INSERT INTO holding_stock (userid, symbol, shares) VALUES (?, ?, ?)", session["user_id"], symbol, shares)

            # 更新余额
            balance = cash - cost
            db.execute("UPDATE users SET cash = ? WHERE id = ?", balance, session["user_id"])

            # 记录交易信息
            db.execute("INSERT INTO transactions (userid, time, symbol, price, shares) VALUES (?, ?, ?, ?, ?)", session["user_id"], datetime.now(), symbol, price, shares)

        # 重定向到 home page
        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    rows = db.execute("SELECT * FROM transactions WHERE userid = ? ORDER BY time", session["user_id"])

    return render_template("history.html", rows=rows)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        # 输入异常处理
        if not symbol:
            return apology("must provide symbol", 400)
        if not lookup(symbol):
            return apology("symbol is inexistence", 400)

        price = lookup(symbol)["price"]
        return render_template("quoted.html", symbol=symbol, price=price)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # 输入异常处理
        if not request.form.get("username"):
            return apology("must provide username", 400)
        if not request.form.get("password"):
            return apology("must provide password", 400)
        if not request.form.get("confirmation"):
            return apology("must provide password-again", 400)

        # 用户名重复检查
        username = request.form.get("username")
        if db.execute("SELECT * from users WHERE username = ?", username):
            return apology("The username already exists", 400)

        # 密码一致性检查
        password = request.form.get("password")
        password_again = request.form.get("confirmation")
        if password != password_again:
            return apology("The password is entered inconsistentl", 400)

        # 插入数据到数据库
        if not db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, generate_password_hash(password)):
            return apology("INSERT error", 400)

        # 重定向到登录页面
        return redirect("/login")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        # 用户持有情况
        holdings = db.execute("SELECT * FROM holding_stock WHERE userid = ?", session["user_id"])

        sell_symbol = request.form.get("symbol")
        # 检查是否为空
        if not sell_symbol:
            return apology("must provide sell_symbol", 400)
        # 检查是否持有该 symbol, 若持有则记录数量, 否则返回报错页面
        for holding in holdings:
            if sell_symbol == holding["symbol"]:
                holding_shares = holding["shares"]
                break
        else:
            return apology("must provide existing sell_symbol", 400)

        sell_shares = request.form.get("shares")
        # 检查卖出数量是否存在
        if not sell_shares:
            return apology("must provide sell_shares", 400)
        # 检查卖出数量是否存为正数字
        if not sell_shares.isdigit():
            return apology("sell_shares should be a numberic", 400)
        sell_shares = float(sell_shares)
        if not sell_shares > 0 or not sell_shares.is_integer():
            return apology("sell_shares should be a positive integer", 400)
        # 检查卖出数量是否正确
        if sell_shares > holding_shares:
            return apology("sell_shares is greater than holding", 400)

        # 更新持有量
        remaining_shares = holding_shares - sell_shares
        db.execute("UPDATE holding_stock SET shares = ? WHERE userid = ? AND symbol = ?", remaining_shares, session["user_id"], sell_symbol)

        # 更新余额
        current_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
        current_price = lookup(sell_symbol)["price"]

        sell_price = current_price * sell_shares
        cash = current_cash + sell_price

        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, session["user_id"])

        # 记录交易信息
        db.execute("INSERT INTO transactions (userid, time, symbol, price, shares) VALUES (?, ?, ?, ?, ?)", session["user_id"], datetime.now(), sell_symbol, current_price, -sell_shares)

        return redirect("/")

    else:
        rows = db.execute("SELECT * FROM holding_stock WHERE userid = ?", session["user_id"])
        return render_template("sell.html", rows=rows)
