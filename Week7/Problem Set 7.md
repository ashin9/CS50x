## Songs

编写 SQL 查询给定的问题

### 要求

- 用一个 SQL 语句，可以嵌套
- 输出准确，仅查询问题所需的数据



3, names of the top 5 longest songs, in descending order of length. 歌曲播放时长，而非歌名长度`LENGTH()`

4, any songs that have danceability, energy, and valence greater than 0.75 任何三者都大于 0.75

8, songs that feature other artists 以其他艺术家命名为特色的歌曲



## Movies

### 要求

同 Songs



表结构

```sql
CREATE TABLE directors (
    movie_id INTEGER NOT NULL,
    person_id INTEGER NOT NULL,
    FOREIGN KEY(movie_id) REFERENCES movies(id),
    FOREIGN KEY(person_id) REFERENCES people(id)
);
CREATE TABLE movies (
    id INTEGER,
    title TEXT NOT NULL,
    year NUMERIC,
    PRIMARY KEY(id)
);
CREATE TABLE people (
    id INTEGER,
    name TEXT NOT NULL,
    birth NUMERIC,
    PRIMARY KEY(id)
);
CREATE TABLE ratings (
    movie_id INTEGER NOT NULL,
    rating REAL NOT NULL,
    votes INTEGER NOT NULL,
    FOREIGN KEY(movie_id) REFERENCES movies(id)
);
CREATE TABLE stars (
    movie_id INTEGER NOT NULL,
    person_id INTEGER NOT NULL,
    FOREIGN KEY(movie_id) REFERENCES movies(id),
    FOREIGN KEY(person_id) REFERENCES people(id)
);
```



11，Chadwick Boseman 演出的前五评分电影名

12，Bradley Cooper 和 Lawrence starred 共同演出的电影名

```sql
SELECT title FROM movies m WHERE
    m.id IN (SELECT m.id FROM movies m JOIN stars s ON m.id = s.movie_id JOIN people p ON p.id = s.person_id AND p.name = "Bradley Cooper")
    AND
    m.id IN (SELECT m.id FROM movies m JOIN stars s ON m.id = s.movie_id JOIN people p ON p.id = s.person_id AND p.name = "Jennifer Lawrence")
    ;
```

13，Kevin Bacon 出演过电影的所有其他明星名字

```sql
SELECT name FROM people WHERE name != "Kevin Bacon" AND
    id IN (
        SELECT s.person_id FROM stars s JOIN movies m ON s.movie_id IN
            (SELECT m.id FROM movies m JOIN stars s ON m.id = s.movie_id JOIN people p ON s.person_id = p.id AND p.name = "Kevin Bacon" AND p.birth = 1958)
        );
```



## [Fiftyville](https://cs50.harvard.edu/x/2024/psets/7/fiftyville/#fiftyville)

CS50 Duck 被偷，识别

- 1，谁偷走了？2，去哪个城市了？3，谁是小偷的帮凶？

已知信息：

- 时间：2023 年 7 月 28
- 地点：Humphrey Street

在数据库中查询数据

在 `log.sql` 中保留 SQL 查询记录，并注释查询原因或思路



注意：保持缩进 [sqlstyle.guide](https://www.sqlstyle.guide/). ，以便阅读



### 表结构

```sql
.tables
airports              crime_scene_reports   people              
atm_transactions      flights               phone_calls         
bakery_security_logs  interviews          
bank_accounts         passengers
```



```sql
CREATE TABLE crime_scene_reports (
    id INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    street TEXT,
    description TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE interviews (
    id INTEGER,
    name TEXT,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    transcript TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE atm_transactions (
    id INTEGER,
    account_number INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    atm_location TEXT,
    transaction_type TEXT,
    amount INTEGER,
    PRIMARY KEY(id)
);
CREATE TABLE bank_accounts (
    account_number INTEGER,
    person_id INTEGER,
    creation_year INTEGER,
    FOREIGN KEY(person_id) REFERENCES people(id)
);
CREATE TABLE airports (
    id INTEGER,
    abbreviation TEXT,
    full_name TEXT,
    city TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE flights (
    id INTEGER,
    origin_airport_id INTEGER,
    destination_airport_id INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    hour INTEGER,
    minute INTEGER,
    PRIMARY KEY(id),
    FOREIGN KEY(origin_airport_id) REFERENCES airports(id),
    FOREIGN KEY(destination_airport_id) REFERENCES airports(id)
);
CREATE TABLE passengers (
    flight_id INTEGER,
    passport_number INTEGER,
    seat TEXT,
    FOREIGN KEY(flight_id) REFERENCES flights(id)
);
CREATE TABLE phone_calls (
    id INTEGER,
    caller TEXT,
    receiver TEXT,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    duration INTEGER,
    PRIMARY KEY(id)
);
CREATE TABLE people (
    id INTEGER,
    name TEXT,
    phone_number TEXT,
    passport_number INTEGER,
    license_plate TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE bakery_security_logs (
    id INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    hour INTEGER,
    minute INTEGER,
    activity TEXT,
    license_plate TEXT,
    PRIMARY KEY(id)
);
```



### 正确思路

```sql
-- 查看所有表
.tables
.schema

-- 查看犯罪场景记录
SELECT *
FROM crime_scene_reports
WHERE year = 2023
	AND month = 7
	AND street LIKE "%Humphrey Street%";
具体时间：上午 10:15
具体地点：面包店 bakery

-- 查看访谈，找线索
SELECT *
FROM interviews
WHERE year = 2023
	AND month = 7
	AND day = 28;
在盗窃发生后不到十分钟的某个时候，我看到小偷在面包店停车场上了一辆车，然后开车走了。如果您有面包店停车场的安全录像，您可能想寻找在该时间段内离开停车场的汽车。  
我不知道小偷的名字，但那是我认识的人。今天早上，在我到达艾玛的面包店之前，我走过莱格特街的自动取款机，看到那里的小偷正在取钱。 
当小偷离开面包店时，他们打电话给一个与他们交谈不到一分钟的人。在电话里，我听到小偷说他们打算明天乘坐最早的航班离开五十维尔。然后，小偷要求电话另一端的人购买机票。

-- 筛选在偷窃发生后，从停车场出去的日志
SELECT *
FROM bakery_security_logs
WHERE year = 2023
	AND month = 7
	AND day = 28
	AND hour = 10
	AND minute >= 15
	AND minute <= 25;
select * from people where license_plate in (select license_plate from bakery_security_logs where year = 2023 and month = 7 and day = 28 and hour = 10 and minute >= 15 and minute <= 25;);

SELECT *
FROM people
WHERE license_plate IN (
	SELECT license_plate
	FROM bakery_security_logs
	WHERE year = 2023
		AND month = 7
		AND day = 28
		AND hour = 10
		AND minute >= 15
		AND minute <= 25
);
+--------+---------+----------------+-----------------+---------------+
|   id   |  name   |  phone_number  | passport_number | license_plate |
+--------+---------+----------------+-----------------+---------------+
| 221103 | Vanessa | (725) 555-4692 | 2963008352      | 5P2BI95       |
| 243696 | Barry   | (301) 555-4174 | 7526138472      | 6P58WS2       |
| 396669 | Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       |
| 398010 | Sofia   | (130) 555-0289 | 1695452385      | G412CB7       |
| 467400 | Luca    | (389) 555-5198 | 8496433585      | 4328GD8       |
| 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
| 560886 | Kelsey  | (499) 555-9472 | 8294398571      | 0NTHK55       |
| 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
+--------+---------+----------------+-----------------+---------------+

-- 当前上午取款的人
SELECT DISTINCT name
FROM people p
	JOIN bank_accounts ba
	ON p.id = ba.person_id
		AND p.license_plate IN (
			SELECT license_plate
			FROM bakery_security_logs
			WHERE year = 2023
				AND month = 7
				AND day = 28
				AND hour = 10
				AND minute >= 15
				AND minute <= 25
		)
	JOIN atm_transactions at
	ON at.account_number = ba.account_number
		AND at.atm_location = "Leggett Street"
		AND at.year = 2023
		AND at.month = 7
		AND at.day = 28;
+-------+
| name  |
+-------+
| Bruce |
| Diana |
| Iman  |
| Luca  |
+-------+

-- 离开面包店时，播出通话时间小于 1 min 的人
SELECT DISTINCT name
FROM people p
	JOIN phone_calls pc
	ON p.phone_number = pc.caller
		AND pc.duration < 60
		AND pc.year = 2023
		AND pc.month = 7
		AND pc.day = 28;
+---------+
|  name   |
+---------+
| Sofia   |
| Kelsey  |
| Bruce   |
| Taylor  |
| Diana   |
| Carina  |
| Kenny   |
| Benista |
+---------+

-- 购买 29 号最早航班离开 fiftyville
SELECT *
FROM flights f
	JOIN airports ap
	ON f.origin_airport_id = ap.id
		AND ap.city = "Fiftyville"
		AND f.year = 2023
		AND f.month = 7
		AND f.day = 29
ORDER BY hour, minute
LIMIT 1;
36

SELECT name
FROM people
WHERE passport_number IN (
	SELECT passport_number
	FROM passengers
	WHERE flight_id = 36
);
+--------+
|  name  |
+--------+
| Kenny  |
| Sofia  |
| Taylor |
| Luca   |
| Kelsey |
| Edward |
| Bruce  |
| Doris  |
+--------+

只有 Bruce 在上面三个集合中
SELECT *
FROM phone_calls pc
WHERE pc.caller = "(367) 555-5533"
	AND pc.duration < 60
	AND pc.year = 2023
	AND pc.month = 7
	AND pc.day = 28;
+-----+----------------+----------------+------+-------+-----+----------+
| id  |     caller     |    receiver    | year | month | day | duration |
+-----+----------------+----------------+------+-------+-----+----------+
| 233 | (367) 555-5533 | (375) 555-8161 | 2023 | 7     | 28  | 45       |
+-----+----------------+----------------+------+-------+-----+----------+

SELECT *
FROM people
WHERE phone_number = "(375) 555-8161";
Robin
```





1，从 `crime_scene_reports` 开始

```sql
select * from crime_scene_reports where year = 2023 and month = 7 and street like "%Humphrey Street%";
+-----+------+-------+-----+-----------------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| id  | year | month | day |     street      |                                                                                                       description                                                                                                        |
+-----+------+-------+-----+-----------------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| 254 | 2023 | 7     | 6   | Humphrey Street | Shoplifting took place at 04:45. Two people witnessed the event.                                                                                                                                                         |
| 295 | 2023 | 7     | 28  | Humphrey Street | Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery. |
| 297 | 2023 | 7     | 28  | Humphrey Street | Littering took place at 16:36. No known witnesses.                                                                                                                                                                       |
| 299 | 2023 | 7     | 30  | Humphrey Street | Littering took place at 17:49. Two people witnessed the event.                                                                                                                                                           |
+-----+------+-------+-----+-----------------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+


Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.

具体时间：上午 10:15
具体地点：面包店 bakery

Littering took place at 16:36. No known witnesses.

时间：下午 16:36
事件：乱扔垃圾
```

2，看下访谈

```sql
select * from interviews where year = 2023 and month = 7 and day = 28;
| 161 | Ruth    | 2023 | 7     | 28  | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
| 162 | Eugene  | 2023 | 7     | 28  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's' bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money. 

| 163 | Raymond | 2023 | 7     | 28  | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |

在盗窃发生后不到十分钟的某个时候，我看到小偷在面包店停车场上了一辆车，然后开车走了。如果您有面包店停车场的安全录像，您可能想寻找在该时间段内离开停车场的汽车。  
我不知道小偷的名字，但那是我认识的人。今天早上，在我到达艾玛的面包店之前，我走过莱格特街的自动取款机，看到那里的小偷正在取钱。 
当小偷离开面包店时，他们打电话给一个与他们交谈不到一分钟的人。在电话里，我听到小偷说他们打算明天乘坐最早的航班离开五十维尔。然后，小偷要求电话另一端的人购买机票。
```

3，看下面包店安全日志

```sql
select * from bakery_security_logs where year = 2023 and month = 7 and day = 28 and hour = 10 and minute = 15;
select * from bakery_security_logs where year = 2023 and month = 7 and day = 28 and hour = 10;

+-----+------+-------+-----+------+--------+----------+---------------+
| id  | year | month | day | hour | minute | activity | license_plate |
+-----+------+-------+-----+------+--------+----------+---------------+
| 258 | 2023 | 7     | 28  | 10   | 8      | entrance | R3G7486       |
| 259 | 2023 | 7     | 28  | 10   | 14     | entrance | 13FNH73       |
| 260 | 2023 | 7     | 28  | 10   | 16     | exit     | 5P2BI95       |
| 261 | 2023 | 7     | 28  | 10   | 18     | exit     | 94KL13X       |
| 262 | 2023 | 7     | 28  | 10   | 18     | exit     | 6P58WS2       |
| 263 | 2023 | 7     | 28  | 10   | 19     | exit     | 4328GD8       |
| 264 | 2023 | 7     | 28  | 10   | 20     | exit     | G412CB7       |
| 265 | 2023 | 7     | 28  | 10   | 21     | exit     | L93JTIZ       |
| 266 | 2023 | 7     | 28  | 10   | 23     | exit     | 322W7JE       |
| 267 | 2023 | 7     | 28  | 10   | 23     | exit     | 0NTHK55       |
| 268 | 2023 | 7     | 28  | 10   | 35     | exit     | 1106N58       |
| 269 | 2023 | 7     | 28  | 10   | 42     | entrance | NRYN856       |
| 270 | 2023 | 7     | 28  | 10   | 44     | entrance | WD5M8I6       |
| 271 | 2023 | 7     | 28  | 10   | 55     | entrance | V47T75I       |
+-----+------+-------+-----+------+--------+----------+---------------+

进入面包店时间在偷窃前的日志
select license_plate from bakery_security_logs where year = 2023 and month = 7 and day = 28 and hour <= 10 and minute <= 15 and activity = "entrance";
+---------------+
| license_plate |
+---------------+
| 1M92998       |
| N507616       |
| 7Z8B130       |
| 47MEFVA       |
| D965M59       |
| HW0488P       |
| 4328GD8       |
| 5P2BI95       |
| R3G7486       |
| 13FNH73       |
+---------------+

进入面包店时间在偷窃前，且离开时间在偷窃后的日志
select * from bakery_security_logs where year = 2023 and month = 7 and day = 28 and hour >=10 and minute >= 15 and activity = "exit" and license_plate in (select license_plate from bakery_security_logs where year = 2023 and month = 7 and day = 28 and hour <= 10 and minute <= 15 and activity = "entrance");
+-----+------+-------+-----+------+--------+----------+---------------+
| id  | year | month | day | hour | minute | activity | license_plate |
+-----+------+-------+-----+------+--------+----------+---------------+
| 260 | 2023 | 7     | 28  | 10   | 16     | exit     | 5P2BI95       |
| 263 | 2023 | 7     | 28  | 10   | 19     | exit     | 4328GD8       |
| 288 | 2023 | 7     | 28  | 17   | 15     | exit     | 13FNH73       |
| 290 | 2023 | 7     | 28  | 17   | 18     | exit     | R3G7486       |
+-----+------+-------+-----+------+--------+----------+---------------+

嫌疑人四个：5P2BI95、4328GD8、13FNH73、R3G7486

前两位只来过店里一次，而且两人进店离店时间很接近，很可能是两人团伙

select * from bakery_security_logs where license_plate = "5P2BI95";
+-----+------+-------+-----+------+--------+----------+---------------+
| id  | year | month | day | hour | minute | activity | license_plate |
+-----+------+-------+-----+------+--------+----------+---------------+
| 255 | 2023 | 7     | 28  | 9    | 15     | entrance | 5P2BI95       |
| 260 | 2023 | 7     | 28  | 10   | 16     | exit     | 5P2BI95       |
+-----+------+-------+-----+------+--------+----------+---------------+

select * from bakery_security_logs where license_plate = "4328GD8";
+-----+------+-------+-----+------+--------+----------+---------------+
| id  | year | month | day | hour | minute | activity | license_plate |
+-----+------+-------+-----+------+--------+----------+---------------+
| 254 | 2023 | 7     | 28  | 9    | 14     | entrance | 4328GD8       |
| 263 | 2023 | 7     | 28  | 10   | 19     | exit     | 4328GD8       |
+-----+------+-------+-----+------+--------+----------+---------------+

后两位应该是常客，而且并没有离开城市，根据题目已有信息推测可以排除掉

select * from bakery_security_logs where license_plate = "13FNH73";
+-----+------+-------+-----+------+--------+----------+---------------+
| id  | year | month | day | hour | minute | activity | license_plate |
+-----+------+-------+-----+------+--------+----------+---------------+
| 169 | 2023 | 7     | 27  | 11   | 11     | entrance | 13FNH73       |
| 187 | 2023 | 7     | 27  | 13   | 25     | exit     | 13FNH73       |
| 259 | 2023 | 7     | 28  | 10   | 14     | entrance | 13FNH73       |
| 288 | 2023 | 7     | 28  | 17   | 15     | exit     | 13FNH73       |
| 320 | 2023 | 7     | 29  | 12   | 49     | entrance | 13FNH73       |
| 335 | 2023 | 7     | 29  | 16   | 20     | exit     | 13FNH73       |
| 357 | 2023 | 7     | 30  | 9    | 12     | entrance | 13FNH73       |
| 420 | 2023 | 7     | 30  | 16   | 5      | exit     | 13FNH73       |
+-----+------+-------+-----+------+--------+----------+---------------+
select * from bakery_security_logs where license_plate = "R3G7486";
+-----+------+-------+-----+------+--------+----------+---------------+
| id  | year | month | day | hour | minute | activity | license_plate |
+-----+------+-------+-----+------+--------+----------+---------------+
| 258 | 2023 | 7     | 28  | 10   | 8      | entrance | R3G7486       |
| 290 | 2023 | 7     | 28  | 17   | 18     | exit     | R3G7486       |
| 352 | 2023 | 7     | 30  | 8    | 33     | entrance | R3G7486       |
| 436 | 2023 | 7     | 30  | 17   | 55     | exit     | R3G7486       |
+-----+------+-------+-----+------+--------+----------+---------------+

严重嫌疑人两个：5P2BI95、4328GD8
```

4，查看嫌疑人信息

```sql
select * from people where license_plate = "5P2BI95";
+--------+---------+----------------+-----------------+---------------+
|   id   |  name   |  phone_number  | passport_number | license_plate |
+--------+---------+----------------+-----------------+---------------+
| 221103 | Vanessa | (725) 555-4692 | 2963008352      | 5P2BI95       |
+--------+---------+----------------+-----------------+---------------+


select * from people where license_plate = "4328GD8";
+--------+------+----------------+-----------------+---------------+
|   id   | name |  phone_number  | passport_number | license_plate |
+--------+------+----------------+-----------------+---------------+
| 467400 | Luca | (389) 555-5198 | 8496433585      | 4328GD8       |
+--------+------+----------------+-----------------+---------------+
```

5，查看嫌疑人护照和手机号对应能找到的线索

```sql
select * from passengers where passport_number = 2963008352;
+-----------+-----------------+------+
| flight_id | passport_number | seat |
+-----------+-----------------+------+
| 2         | 2963008352      | 6C   |
| 20        | 2963008352      | 6B   |
| 39        | 2963008352      | 8C   |
+-----------+-----------------+------+

航班 id ：2、20、39

select * from phone_calls where caller = "(725) 555-4692" or receiver = "(725) 555-4692" order by day;
+-----+----------------+----------------+------+-------+-----+----------+
| id  |     caller     |    receiver    | year | month | day | duration |
+-----+----------------+----------------+------+-------+-----+----------+
| 64  | (725) 555-4692 | (604) 555-0153 | 2023 | 7     | 25  | 528      |
| 257 | (725) 555-4692 | (821) 555-5262 | 2023 | 7     | 28  | 456      |
| 334 | (911) 555-0229 | (725) 555-4692 | 2023 | 7     | 29  | 296      |
| 371 | (035) 555-2997 | (725) 555-4692 | 2023 | 7     | 29  | 113      |
| 390 | (356) 555-6641 | (725) 555-4692 | 2023 | 7     | 30  | 224      |
| 502 | (725) 555-4692 | (962) 555-5827 | 2023 | 7     | 31  | 272      |
+-----+----------------+----------------+------+-------+-----+----------+
没有太大疑点

select * from passengers where passport_number = 8496433585;
+-----------+-----------------+------+
| flight_id | passport_number | seat |
+-----------+-----------------+------+
| 11        | 8496433585      | 5D   |
| 36        | 8496433585      | 7B   |
| 48        | 8496433585      | 7C   |
+-----------+-----------------+------+
航班 id ：11、36、48

select * from phone_calls where caller = "(389) 555-5198" or receiver = "(389) 555-5198" order by day;
+-----+----------------+----------------+------+-------+-----+----------+
| id  |     caller     |    receiver    | year | month | day | duration |
+-----+----------------+----------------+------+-------+-----+----------+
| 57  | (389) 555-5198 | (368) 555-3561 | 2023 | 7     | 25  | 414      |
| 227 | (544) 555-8087 | (389) 555-5198 | 2023 | 7     | 28  | 595      |
| 234 | (609) 555-5876 | (389) 555-5198 | 2023 | 7     | 28  | 60       |
| 326 | (389) 555-5198 | (609) 555-5876 | 2023 | 7     | 29  | 397      |
| 408 | (609) 555-5876 | (389) 555-5198 | 2023 | 7     | 30  | 255      |
+-----+----------------+----------------+------+-------+-----+----------+
通话时间都大于等于一分钟

疑点：在偷窃时间先后和 (609) 555-5876 来回通话多次

select * from people where phone_number = "(609) 555-5876";
+--------+---------+----------------+-----------------+---------------+
|   id   |  name   |  phone_number  | passport_number | license_plate |
+--------+---------+----------------+-----------------+---------------+
| 561160 | Kathryn | (609) 555-5876 | 6121106406      | 4ZY7I8T       |
+--------+---------+----------------+-----------------+---------------+
帮凶可能是：Kathryn
```

6，查看航班情况

```sql
select * from flights where id = 2 or id = 20 or id = 39 order by day;
+----+-------------------+------------------------+------+-------+-----+------+--------+
| id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
+----+-------------------+------------------------+------+-------+-----+------+--------+
| 39 | 5                 | 8                      | 2023 | 7     | 27  | 22   | 37     |
| 20 | 6                 | 8                      | 2023 | 7     | 28  | 15   | 22     |
| 2  | 2                 | 8                      | 2023 | 7     | 30  | 12   | 44     |
+----+-------------------+------------------------+------+-------+-----+------+--------+
没有从 destination_airport_id = 8（Fiftyville） 走的航班，所以可排除嫌疑

select * from flights where id = 11 or id = 36 or id = 48 order by day;
+----+-------------------+------------------------+------+-------+-----+------+--------+
| id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
+----+-------------------+------------------------+------+-------+-----+------+--------+
| 36 | 8                 | 4                      | 2023 | 7     | 29  | 8    | 20     |
| 11 | 8                 | 12                     | 2023 | 7     | 30  | 13   | 7      |
| 48 | 5                 | 8                      | 2023 | 7     | 30  | 18   | 28     |
+----+-------------------+------------------------+------+-------+-----+------+--------+
29 号最早的航班，嫌疑人是 Luca


select * from airports where id = 8 or id = 4 or id = 12;
+----+--------------+-----------------------------+------------+
| id | abbreviation |          full_name          |    city    |
+----+--------------+-----------------------------+------------+
| 8  | CSF          | Fiftyville Regional Airport | Fiftyville |
+----+--------------+-----------------------------+------------+

select * from airports where id = 4 or id = 12;
+----+--------------+-------------------------------------+---------------+
| id | abbreviation |              full_name              |     city      |
+----+--------------+-------------------------------------+---------------+
| 4  | LGA          | LaGuardia Airport                   | New York City |
| 12 | DEL          | Indira Gandhi International Airport | Delhi         |
+----+--------------+-------------------------------------+---------------+

可能去了：New York City
```

7，查看银行转账记录

```sql
select * from bank_accounts where person_id = 467400 or person_id = 561160;
+----------------+-----------+---------------+
| account_number | person_id | creation_year |
+----------------+-----------+---------------+
| 28500762       | 467400    | 2014          |
+----------------+-----------+---------------+

select * from atm_transactions where account_number = 28500762;
+-----+----------------+------+-------+-----+----------------+------------------+--------+
| id  | account_number | year | month | day |  atm_location  | transaction_type | amount |
+-----+----------------+------+-------+-----+----------------+------------------+--------+
| 7   | 28500762       | 2023 | 7     | 26  | Leggett Street | deposit          | 75     |
| 246 | 28500762       | 2023 | 7     | 28  | Leggett Street | withdraw         | 48     |
+-----+----------------+------+-------+-----+----------------+------------------+--------+

```

### 以上推理思路错误

```sql
-- 查看所有表
.tables
.schema

-- 1, 查看 crime_scene_reports
SELECT *
FROM crime_scene_reports
WHERE year = 2023
	AND month = 7
	AND street LIKE "%Humphrey Street%";
-- 2, 查看 interviews
SELECT *
FROM interviews
WHERE year = 2023
	AND month = 7
	AND day = 28;
-- 3, 查看 bakery_security_logs
SELECT *
FROM bakery_security_logs
WHERE year = 2023
	AND month = 7
	AND day = 28
	AND hour = 10
	AND minute = 15;
	
SELECT *
FROM bakery_security_logs
WHERE year = 2023
	AND month = 7
	AND day = 28
	AND hour = 10;
-- 进入面包店时间在偷窃前的日志
SELECT license_plate
FROM bakery_security_logs
WHERE year = 2023
	AND month = 7
	AND day = 28
	AND hour <= 10
	AND minute <= 15
	AND activity = "entrance";
-- 进入面包店时间在偷窃前，且离开时间在偷窃后的日志
SELECT *
FROM bakery_security_logs
WHERE year = 2023
	AND month = 7
	AND day = 28
	AND hour >= 10
	AND minute >= 15
	AND activity = "exit"
	AND license_plate IN (
		SELECT license_plate
		FROM bakery_security_logs
		WHERE year = 2023
			AND month = 7
			AND day = 28
			AND hour <= 10
			AND minute <= 15
			AND activity = "entrance"
	);
-- 查看嫌疑人
select * from bakery_security_logs where license_plate = "5P2BI95";
select * from bakery_security_logs where license_plate = "4328GD8";

-- 4, 查看嫌疑人信息
select * from people where license_plate = "5P2BI95";
select * from people where license_plate = "4328GD8";

-- 5, 查看嫌疑人护照和手机号对应能找到的线索
-- 查看航班
select * from passengers where passport_number = 2963008352;
select * from passengers where passport_number = 8496433585;
-- 查看通话记录
select * from phone_calls where caller = "(725) 555-4692" or receiver = "(725) 555-4692" order by day;
select * from phone_calls where caller = "(389) 555-5198" or receiver = "(389) 555-5198" order by day;

-- 6, 查看航班情况
select * from flights where id = 2 or id = 20 or id = 39 order by day;
select * from flights where id = 11 or id = 36 or id = 48 order by day;
-- 查看航班目的地
select * from airports where id = 8 or id = 4 or id = 12;

-- 7, 查看银行转账记录
select * from bank_accounts where person_id = 467400 or person_id = 561160;
select * from atm_transactions where account_number = 28500762;
```



错误原因：

- 一开始没看到访谈记录
- 进入和离开面包店的人筛选有问题，可能多天前开车进入的

