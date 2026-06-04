// SPDX-FileCopyrightText: 2019 - 2026 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "test_huanglidatabase.h"
#include "../third-party_stub/stub.h"
#include "config.h"

bool stub_huangli_dbOpen(void *obj)
{
    Q_UNUSED(obj);
    return true;
}

test_huanglidatabase::test_huanglidatabase()
{
    Stub stub;
    stub.set(ADDR(DHuangLiDataBase, dbOpen), stub_huangli_dbOpen);
    hlDb = new DHuangLiDataBase();
}

test_huanglidatabase::~test_huanglidatabase()
{
    if (hlDb->m_database.isOpen()) {
        hlDb->m_database.close();
    }
    delete hlDb;
}

//QJsonArray DHuangLiDataBase::queryFestivalList(quint32 year, quint8 month)
TEST_F(test_huanglidatabase, QueryFestivalList)
{
    quint32 year = 2020;
    quint8 month = 10;
    QJsonArray getFes = hlDb->queryFestivalList(year, month);
}

//QList<stHuangLi> DHuangLiDataBase::queryHuangLiByDays(const QList<stDay> &days)
TEST_F(test_huanglidatabase, QueryHuangLiByDays)
{
    QList<stDay> days;
    stDay day1, day2;
    day1.Year = day2.Year = 2020;
    day1.Month = day2.Month = 10;
    day1.Day = 1;
    day2.Day = 2;
    days << day1 << day2;

    QList<stHuangLi> getHuangli = hlDb->queryHuangLiByDays(days);

    stHuangLi hl1, hl2;
    hl1 = getHuangli.at(0);
    hl2 = getHuangli.at(1);
    QString hl2Suit = "开光.解除.起基.动土.拆卸.上梁.立碑.修坟.安葬.破土.启攒.移柩.";
    QString hl2Avoid = "嫁娶.出行.安床.作灶.祭祀.入宅.移徙.出火.进人口.置产.";
    assert(20201001 == hl1.ID && 20201002 == hl2.ID);
    assert(hl2Suit == hl2.Suit && hl2Avoid == hl2.Avoid);
}

////bool HuangLiDataBase::OpenHuangliDatabase(const QString &dbpath)
//TEST_F(test_huanglidatabase, OpenHuangliDatabase)
//{
//    QString dbpath = "";
//    hlDb->OpenHuangliDatabase(dbpath);

//    dbpath = "123123";
//    hlDb->OpenHuangliDatabase(dbpath);

//    dbpath = "%s%s%s%s%s%s";
//    hlDb->OpenHuangliDatabase(dbpath);

//    hlDb->OpenHuangliDatabase(HL_DATABASE_DIR);
//}
