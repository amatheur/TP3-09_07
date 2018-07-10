#include "gtest/gtest.h"

#include "../src/Instruccion.h"
#include "../src/Programa.h"

TEST(test_programa, rutinaExistente) {
    Programa p;
    p.AgregarInstruccion("a", Instruccion(10));
    p.AgregarInstruccion("a", Instruccion(oAdd));
    EXPECT_EQ(p.Longitud("a"), 2);
    p.AgregarInstruccion("b", Instruccion(oWrite, "z"));
    EXPECT_EQ(p.Longitud("a")>0, true);
    EXPECT_EQ(p.Longitud("b")>0, true);
}

TEST(test_programa, longitud) {
    Programa p;
    p.AgregarInstruccion("foo", Instruccion(10));
    EXPECT_EQ(p.Longitud("foo"), 1);
    p.AgregarInstruccion("foo", Instruccion(oAdd));
    EXPECT_EQ(p.Longitud("foo"), 2);
    p.AgregarInstruccion("foo", Instruccion(12));
    EXPECT_EQ(p.Longitud("foo"), 3);
    p.AgregarInstruccion("foo", Instruccion(oMul));
    EXPECT_EQ(p.Longitud("foo"), 4);
}

TEST(test_programa, instruccion) {
    Programa p;
    p.AgregarInstruccion("X", Instruccion(oRead, "x"));
    p.AgregarInstruccion("X", Instruccion(2));
    p.AgregarInstruccion("X", Instruccion(oMul));
    p.AgregarInstruccion("X", Instruccion(oRead, "y"));
    p.AgregarInstruccion("X", Instruccion(oAdd));
    EXPECT_EQ(p.Longitud("X"), 5);
    EXPECT_EQ(p.instruccion("X", 0).operacion(), oRead);
    EXPECT_EQ(p.instruccion("X", 0).variable(), "x");
    EXPECT_EQ(p.instruccion("X", 1).operacion(), oPush);
    EXPECT_EQ(p.instruccion("X", 1).Valor(), 2);
    EXPECT_EQ(p.instruccion("X", 2).operacion(), oMul);
    EXPECT_EQ(p.instruccion("X", 3).operacion(), oRead);
    EXPECT_EQ(p.instruccion("X", 3).variable(), "y");
    EXPECT_EQ(p.instruccion("X", 4).operacion(), oAdd);
}

TEST(test_programa, dosRutinas) {
    Programa p;
    p.AgregarInstruccion("A", Instruccion(oRead, "a"));
    p.AgregarInstruccion("B", Instruccion(oWrite, "b"));
    p.AgregarInstruccion("A", Instruccion(oJump, "c"));
    p.AgregarInstruccion("B", Instruccion(oJumpz, "d"));
    p.AgregarInstruccion("A", Instruccion(oRead, "e"));

    EXPECT_EQ(p.Longitud("A"), 3);
    EXPECT_EQ(p.Longitud("B"), 2);
    EXPECT_EQ(p.instruccion("A", 0).operacion(), oRead);
    EXPECT_EQ(p.instruccion("A", 0).variable(), "a");
    EXPECT_EQ(p.instruccion("A", 1).operacion(), oJump);
    EXPECT_EQ(p.instruccion("A", 1).rutina(), "c");
    EXPECT_EQ(p.instruccion("A", 2).operacion(), oRead);
    EXPECT_EQ(p.instruccion("A", 2).variable(), "e");

    EXPECT_EQ(p.instruccion("B", 0).operacion(), oWrite);
    EXPECT_EQ(p.instruccion("B", 0).variable(), "b");
    EXPECT_EQ(p.instruccion("B", 1).operacion(), oJumpz);
    EXPECT_EQ(p.instruccion("B", 1).rutina(), "d");
}

