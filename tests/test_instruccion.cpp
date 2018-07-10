#include "gtest/gtest.h"

#include "../src/Instruccion.h"

TEST(test_instruccion, i_push) {
    Instruccion i(121);
    EXPECT_EQ(i.operacion(), oPush);
    EXPECT_EQ(i.Valor(), 121);
}

TEST(test_instruccion, i_add) {
    Instruccion i(oAdd);
    EXPECT_EQ(i.operacion(), oAdd);
}

TEST(test_instruccion, i_sub) {
    Instruccion i(oSub);
    EXPECT_EQ(i.operacion(), oSub);
}

TEST(test_instruccion, i_mul) {
    Instruccion i(oMul);
    EXPECT_EQ(i.operacion(), oMul);
}

TEST(test_instruccion, i_read) {
    Instruccion i(oRead, "foo");
    EXPECT_EQ(i.operacion(), oRead);
    EXPECT_EQ(i.variable(), "foo");
}

TEST(test_instruccion, i_write) {
    Instruccion i(oWrite, "bar");
    EXPECT_EQ(i.operacion(), oWrite);
    EXPECT_EQ(i.variable(), "bar");
}

TEST(test_instruccion, i_jump) {
    Instruccion i(oJump, "baz");
    EXPECT_EQ(i.operacion(), oJump);
    EXPECT_EQ(i.rutina(), "baz");
}

TEST(test_instruccion, i_jumpz) {
    Instruccion i(oJumpz, "quux");
    EXPECT_EQ(i.operacion(), oJumpz);
    EXPECT_EQ(i.rutina(), "quux");
}

