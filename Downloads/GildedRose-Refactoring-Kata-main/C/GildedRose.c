#include <string.h>
#include "GildedRose.h"
#include <stdio.h>

Item*
init_item(Item* item, const char *name, int sellIn, int quality)
{
    item->sellIn = sellIn;
    item->quality = quality;
    item->name = strdup(name);
    
    return item;
}

extern char* 
print_item(char* buffer, Item* item) 
{
    sprintf(buffer, "%s, %d, %d", item->name, item->sellIn, item->quality);
    return buffer;
}

static void increase_quality(Item* item, int amount)
{
    item->quality += amount;
    if (item->quality > 50)
    {
        item->quality = 50;
    }
}

static void decrease_quality(Item* item, int amount)
{
    item->quality -= amount;
    if (item->quality < 0)
    {
        item->quality = 0;
    }
}

static void update_normal_item(Item* item)
{
    item->sellIn -= 1;
    decrease_quality(item, item->sellIn < 0 ? 2 : 1);
}

static void update_aged_brie(Item* item)
{
    item->sellIn -= 1;
    increase_quality(item, item->sellIn < 0 ? 2 : 1);
}

static void update_sulfuras(Item* item)
{
    item->quality = 80;
}

static void update_backstage_pass(Item* item)
{
    item->sellIn -= 1;

    if (item->sellIn < 0)
    {
        item->quality = 0;
    }
    else if (item->sellIn < 5)
    {
        increase_quality(item, 3);
    }
    else if (item->sellIn < 10)
    {
        increase_quality(item, 2);
    }
    else
    {
        increase_quality(item, 1);
    }
}

static void update_conjured_item(Item* item)
{
    item->sellIn -= 1;
    decrease_quality(item, item->sellIn < 0 ? 4 : 2);
}

void update_quality(Item items[], int size)
{
    int i;

    for (i = 0; i < size; i++)
    {
        if (strcmp(items[i].name, "Aged Brie") == 0)
        {
            update_aged_brie(items + i);
        }
        else if (strcmp(items[i].name, "Sulfuras, Hand of Ragnaros") == 0)
        {
            update_sulfuras(items + i);
        }
        else if (strcmp(items[i].name, "Backstage passes to a TAFKAL80ETC concert") == 0)
        {
            update_backstage_pass(items + i);
        }
        else if (strncmp(items[i].name, "Conjured", 8) == 0)
        {
            update_conjured_item(items + i);
        }
        else
        {
            update_normal_item(items + i);
        }
    }
}
