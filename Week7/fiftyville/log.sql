-- Keep a log of any SQL queries you execute as you solve the mystery.

-- 查看所有表
.tables
.schema

-- 查看犯罪场景记录
SELECT *
FROM crime_scene_reports
WHERE year = 2023
	AND month = 7
	AND street LIKE "%Humphrey Street%";
-- 具体时间：上午 10:15
-- 具体地点：面包店 bakery

-- 查看访谈，找线索
SELECT *
FROM interviews
WHERE year = 2023
	AND month = 7
	AND day = 28;
-- 在盗窃发生后不到十分钟的某个时候，我看到小偷在面包店停车场上了一辆车，然后开车走了。如果您有面包店停车场的安全录像，您可能想寻找在该时间段内离开停车场的汽车。
-- 我不知道小偷的名字，但那是我认识的人。今天早上，在我到达艾玛的面包店之前，我走过莱格特街的自动取款机，看到那里的小偷正在取钱。
-- 当小偷离开面包店时，他们打电话给一个与他们交谈不到一分钟的人。在电话里，我听到小偷说他们打算明天乘坐最早的航班离开五十维尔。然后，小偷要求电话另一端的人购买机票。

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
-- 36

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

-- 只有 Bruce 在上面三个集合中
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
-- Robin
