## [Passwords](https://cs50.harvard.edu/x/2024/notes/cybersecurity/#passwords)

弱口令

规律推断

字典

爆破攻击

指数增长尝试间隔延迟，增加攻击的时间成本和门槛

## [Password Managers](https://cs50.harvard.edu/x/2024/notes/cybersecurity/#password-managers)

密码管理器

- 问题：若被破解则泄露所有密码

## [Two-factor Authentication](https://cs50.harvard.edu/x/2024/notes/cybersecurity/#two-factor-authentication)

Two-factor authentication，双因素认证，显著增加安全性

One-time passwords，一次一密

## hashing，哈希表

rainbow table，彩虹表，构建密码和 hash 表，搜索对比哈希来破解明文

问题：两个人相同密码，则 hash 值也想同，一定程度泄露信息

解决：salt，盐

## Cryptography，密码学

对称加密

共享密钥

非对称加密，公钥、私钥

HTTPS，SSL/TSL

## Passkeys

无密码登录，首次发送证书，后续访问本地私钥发送验证，类似 SSH 证书登录过程

end-to-end encryption，端到端加密

## [Deletion](https://cs50.harvard.edu/x/2024/notes/cybersecurity/#deletion)

deletion，删除，只是逻辑标记可被覆盖，若没被覆盖则可恢复

secure delete，安全删除，把所有数据 bit 标记 0

flull-disk encryption，全盘加密

ransomware，勒索软件

## [Summing Up](https://cs50.harvard.edu/x/2024/notes/cybersecurity/#summing-up)

- Use a password manager.
- Use two-factor authentication.
- Use (end-to-end) encryption.