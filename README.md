<p align="center">
  <img src="https://static.wikia.nocookie.net/riskofrain2_gamepedia_en/images/b/b7/Lunar_Coin.jpg/revision/latest?cb=20200201131510" />
</p>

# Risk of Rain 2 - Lunar Cheat
Maxes out Lunar Coins for a save.

## Details
Save data for Risk of Rain 2 is stored in an XML file under your Steam User Data. The script regex replaces your existing lunar coins with a near-max value of `2,147,483,640` (7 less than max). Risk of Rain 2 uses a signed 32-bit integer to count the number of coins you have. As such, if you exceed `2,147,483,647` lunar coins, you will encounter an [integer overflow](https://en.wikipedia.org/wiki/Integer_overflow) and will loop to `-2,147,483,647`. The lower value serves as a buffer to prevent this.
