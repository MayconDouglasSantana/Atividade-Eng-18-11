#include <CppUTest/TestHarness.h>
#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTestExt/MockSupport.h>

extern "C" {
#include "GildedRose.h"
}

TEST_GROUP(TestGildedRoseGroup)
{
  void setup() {
  }
  void teardown() {
  }
};

TEST(TestGildedRoseGroup, FirstTest)
{
    Item items[1];
    init_item(items, "Foo", 0, 0);
    update_quality(items, 1);
    LONGS_EQUAL(-1, items[0].sellIn);
    LONGS_EQUAL(0, items[0].quality);
}

TEST(TestGildedRoseGroup, NormalItemDecreasesByOne)
{
    Item items[1];
    init_item(items, "Normal Item", 10, 20);
    update_quality(items, 1);
    LONGS_EQUAL(9, items[0].sellIn);
    LONGS_EQUAL(19, items[0].quality);
}

TEST(TestGildedRoseGroup, NormalItemDecreasesTwiceAsFastAfterSellInZero)
{
    Item items[1];
    init_item(items, "Normal Item", 0, 20);
    update_quality(items, 1);
    LONGS_EQUAL(-1, items[0].sellIn);
    LONGS_EQUAL(18, items[0].quality);
}

TEST(TestGildedRoseGroup, NormalItemQualityDoesNotBecomeNegative)
{
    Item items[1];
    init_item(items, "Normal Item", 10, 0);
    update_quality(items, 1);
    LONGS_EQUAL(9, items[0].sellIn);
    LONGS_EQUAL(0, items[0].quality);
}

TEST(TestGildedRoseGroup, AgedBrieIncreasesQuality)
{
    Item items[1];
    init_item(items, "Aged Brie", 2, 10);
    update_quality(items, 1);
    LONGS_EQUAL(1, items[0].sellIn);
    LONGS_EQUAL(11, items[0].quality);
}

TEST(TestGildedRoseGroup, AgedBrieIncreasesTwiceAsFastAfterSellIn)
{
    Item items[1];
    init_item(items, "Aged Brie", 0, 10);
    update_quality(items, 1);
    LONGS_EQUAL(-1, items[0].sellIn);
    LONGS_EQUAL(12, items[0].quality);
}

TEST(TestGildedRoseGroup, AgedBrieQualityDoesNotExceed50)
{
    Item items[1];
    init_item(items, "Aged Brie", 0, 50);
    update_quality(items, 1);
    LONGS_EQUAL(-1, items[0].sellIn);
    LONGS_EQUAL(50, items[0].quality);
}

TEST(TestGildedRoseGroup, SulfurasNeverChanges)
{
    Item items[1];
    init_item(items, "Sulfuras, Hand of Ragnaros", -1, 80);
    update_quality(items, 1);
    LONGS_EQUAL(-1, items[0].sellIn);
    LONGS_EQUAL(80, items[0].quality);
}

TEST(TestGildedRoseGroup, SulfurasQualityIsAlways80)
{
    Item items[1];
    init_item(items, "Sulfuras, Hand of Ragnaros", 5, 10);
    update_quality(items, 1);
    LONGS_EQUAL(5, items[0].sellIn);
    LONGS_EQUAL(80, items[0].quality);
}

TEST(TestGildedRoseGroup, BackstagePassIncreasesByOneAboveTenDays)
{
    Item items[1];
    init_item(items, "Backstage passes to a TAFKAL80ETC concert", 11, 20);
    update_quality(items, 1);
    LONGS_EQUAL(10, items[0].sellIn);
    LONGS_EQUAL(21, items[0].quality);
}

TEST(TestGildedRoseGroup, BackstagePassIncreasesByTwoAtTenDays)
{
    Item items[1];
    init_item(items, "Backstage passes to a TAFKAL80ETC concert", 10, 20);
    update_quality(items, 1);
    LONGS_EQUAL(9, items[0].sellIn);
    LONGS_EQUAL(22, items[0].quality);
}

TEST(TestGildedRoseGroup, BackstagePassIncreasesByThreeAtFiveDays)
{
    Item items[1];
    init_item(items, "Backstage passes to a TAFKAL80ETC concert", 5, 20);
    update_quality(items, 1);
    LONGS_EQUAL(4, items[0].sellIn);
    LONGS_EQUAL(23, items[0].quality);
}

TEST(TestGildedRoseGroup, BackstagePassDropsToZeroAtSellInZero)
{
    Item items[1];
    init_item(items, "Backstage passes to a TAFKAL80ETC concert", 0, 20);
    update_quality(items, 1);
    LONGS_EQUAL(-1, items[0].sellIn);
    LONGS_EQUAL(0, items[0].quality);
}

TEST(TestGildedRoseGroup, BackstagePassQualityDoesNotExceed50)
{
    Item items[1];
    init_item(items, "Backstage passes to a TAFKAL80ETC concert", 5, 49);
    update_quality(items, 1);
    LONGS_EQUAL(4, items[0].sellIn);
    LONGS_EQUAL(50, items[0].quality);
}

TEST(TestGildedRoseGroup, ConjuredItemDecreasesTwiceAsFast)
{
    Item items[1];
    init_item(items, "Conjured Mana Cake", 3, 20);
    update_quality(items, 1);
    LONGS_EQUAL(2, items[0].sellIn);
    LONGS_EQUAL(18, items[0].quality);
}

TEST(TestGildedRoseGroup, ConjuredItemDecreasesFourTimesAfterSellIn)
{
    Item items[1];
    init_item(items, "Conjured Mana Cake", 0, 20);
    update_quality(items, 1);
    LONGS_EQUAL(-1, items[0].sellIn);
    LONGS_EQUAL(16, items[0].quality);
}

TEST(TestGildedRoseGroup, ConjuredItemQualityDoesNotBecomeNegative)
{
    Item items[2];
    init_item(items, "Conjured Mana Cake", 3, 1);
    init_item(items + 1, "Conjured Mana Cake", 0, 3);
    update_quality(items, 2);
    LONGS_EQUAL(0, items[0].quality);
    LONGS_EQUAL(0, items[1].quality);
}

void example()
{
    Item items[6];
    int last = 0;
    
    init_item(items + last++, "+5 Dexterity Vest", 10, 20);
    init_item(items + last++, "Aged Brie", 2, 0);
    init_item(items + last++, "Elixir of the Mongoose", 5, 7);
    init_item(items + last++, "Sulfuras, Hand of Ragnaros", 0, 80);
    init_item(items + last++, "Backstage passes to a TAFKAL80ETC concert", 15, 20);
    init_item(items + last++, "Conjured Mana Cake", 3, 6);
    update_quality(items, last);
}

int
main(int ac, char** av)
{
  return CommandLineTestRunner::RunAllTests(ac, av);
}
