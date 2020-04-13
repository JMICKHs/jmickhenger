#include "gtest/gtest.h"
#include "../Cache.h"


TEST(testCache, singleton) {
    Cache * t1 = Cache::shared();
    Cache * t2 = Cache::shared();
    ASSERT_EQ(t1, t2);
    ASSERT_EQ(t1 != nullptr, true);
}

TEST(testCache, chatList1) {
    Cache * cache = Cache::shared();
    Info::ChatInfo info(3, "name");
    vector<Info::ChatInfo> vec;
    vec.push_back(info);
    cache->save(vec);
    ASSERT_EQ(cache->getChatList(), vec);
}