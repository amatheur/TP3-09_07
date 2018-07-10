#include "gtest/gtest.h"
#include "../src/Calculadora.h"
#include "../src/Programa.h"
#include "../src/Instruccion.h"

TEST(test_calculadora, variables){

    Programa P;
    P.AgregarInstruccion("A",Instruccion(0));
    Variable x("x");
    Calculadora C(P,"A",10);
    C.AsignarVariable(x,2);
    EXPECT_EQ(C.ValorActual("x"), 2);
}

TEST(test_calculadora, ejecutarPUSH){
    Programa p;
    p.AgregarInstruccion("MAIN", Instruccion(2));
    p.AgregarInstruccion("MAIN", Instruccion(oWrite, "y"));
    Calculadora c(p, "MAIN", 12);
    c.AsignarVariable("y", 0);
    c.EjecutarUnPaso();
    c.EjecutarUnPaso();
    EXPECT_EQ(c.ValorActual("y"), 2);

}

TEST(test_calculadora, ejecutarManejoVariables){
    Programa p;
    p.AgregarInstruccion("MAIN", Instruccion(oRead, "x"));
    p.AgregarInstruccion("MAIN", Instruccion(oWrite, "y"));
    Calculadora c(p,"MAIN",12);
    c.AsignarVariable("x", 2);
    c.AsignarVariable("y", 0);
    c.EjecutarUnPaso();
    c.EjecutarUnPaso();

    EXPECT_EQ(c.ValorActual("y"), 2);

}

TEST(test_calculadora, saltos) {
    Programa p;
    p.AgregarInstruccion("A", Instruccion(5));
    p.AgregarInstruccion("A", Instruccion(oJump, "B"));
    p.AgregarInstruccion("B", Instruccion(oWrite, "x"));

    Calculadora c(p, "A", 12);
    c.EjecutarUnPaso();
    c.EjecutarUnPaso();
    c.EjecutarUnPaso();
    EXPECT_EQ(c.ValorActual("x"), 5);
}

TEST(test_calculadora, saltosz0){
    Programa p;
    p.AgregarInstruccion("A", Instruccion(0));
    p.AgregarInstruccion("A", Instruccion(oJumpz, "B"));
    p.AgregarInstruccion("B", Instruccion(2));
    p.AgregarInstruccion("B", Instruccion(oWrite,"x"));

    Calculadora c(p, "A", 12);
    c.EjecutarUnPaso();
    c.EjecutarUnPaso();
    c.EjecutarUnPaso();
    c.EjecutarUnPaso();
    EXPECT_EQ(c.ValorActual("x"), 2);
}

TEST(test_calculadora, saltoszVacio){
    Programa p;
    p.AgregarInstruccion("A", Instruccion(oJumpz, "B"));
    p.AgregarInstruccion("B", Instruccion(2));
    p.AgregarInstruccion("B", Instruccion(oWrite,"x"));

    Calculadora c(p,"A",12);
    c.EjecutarUnPaso();
    c.EjecutarUnPaso();
    c.EjecutarUnPaso();

    EXPECT_EQ(c.ValorActual("x"), 2);
}

TEST(test_calculadora, terminarRutinaNoDef){
    Programa p1;
    p1.AgregarInstruccion("A", Instruccion(oWrite, "x"));
    p1.AgregarInstruccion("A", Instruccion(oJump, "FIN"));
    p1.AgregarInstruccion("A", Instruccion(oRead, "y"));
    p1.AgregarInstruccion("A", Instruccion(oWrite, "x"));

    Calculadora c1(p1,"A",20);
    c1.AsignarVariable("y",2);
    c1.EjecutarUnPaso();
    c1.EjecutarUnPaso();
    c1.EjecutarUnPaso();
    c1.EjecutarUnPaso();

    EXPECT_EQ(c1.ValorActual("x"), 0);

    Programa p2;
    p2.AgregarInstruccion("A", Instruccion(oWrite, "x"));
    p2.AgregarInstruccion("A", Instruccion(oJumpz, "FIN"));
    p2.AgregarInstruccion("A", Instruccion(2));
    p2.AgregarInstruccion("A", Instruccion(oWrite, "x"));

    Calculadora c2(p2, "A", 20);
    c2.EjecutarUnPaso();
    c2.EjecutarUnPaso();
    c2.EjecutarUnPaso();
    c2.EjecutarUnPaso();

    EXPECT_EQ(c1.ValorActual("x"), 0);

}


TEST(test_calculadora, suma){
    Programa p1;
    p1.AgregarInstruccion("MAIN", Instruccion(30));
    p1.AgregarInstruccion("MAIN", Instruccion(10));
    p1.AgregarInstruccion("MAIN", Instruccion(oAdd));
    p1.AgregarInstruccion("MAIN", Instruccion(oWrite, "x"));

    Calculadora c1(p1, "MAIN", 20);
    c1.EjecutarUnPaso();
    c1.EjecutarUnPaso();
    c1.EjecutarUnPaso();
    c1.EjecutarUnPaso();
    EXPECT_EQ(c1.ValorActual("x"), 40);

    Programa p2;
    p2.AgregarInstruccion("MAIN", Instruccion(oAdd));
    p2.AgregarInstruccion("MAIN", Instruccion(oWrite, "x"));

    Calculadora c2(p2, "MAIN", 20);
    c2.EjecutarUnPaso();
    c2.EjecutarUnPaso();
    EXPECT_EQ(c2.ValorActual("x"), 0);

    Programa p3;
    p3.AgregarInstruccion("MAIN", Instruccion(30));
    p3.AgregarInstruccion("MAIN", Instruccion(oAdd));
    p3.AgregarInstruccion("MAIN", Instruccion(oWrite, "x"));

    Calculadora c3(p3, "MAIN", 20);
    c3.EjecutarUnPaso();
    c3.EjecutarUnPaso();
    c3.EjecutarUnPaso();
    EXPECT_EQ(c3.ValorActual("x"), 30);
}

TEST(test_calculadora, resta){
    Programa p1;
    p1.AgregarInstruccion("MAIN", Instruccion(10));
    p1.AgregarInstruccion("MAIN", Instruccion(5));
    p1.AgregarInstruccion("MAIN", Instruccion(oSub));
    p1.AgregarInstruccion("MAIN", Instruccion(oWrite, "x"));

    Calculadora c1(p1,"MAIN",20);
    c1.EjecutarUnPaso();
    c1.EjecutarUnPaso();
    c1.EjecutarUnPaso();
    c1.EjecutarUnPaso();
    EXPECT_EQ(c1.ValorActual("x"), 5);

    Programa p2;
    p2.AgregarInstruccion("MAIN", Instruccion(oSub));
    p2.AgregarInstruccion("MAIN", Instruccion(oWrite, "x"));

    Calculadora c2(p2,"MAIN", 20
    );
    c2.EjecutarUnPaso();
    c2.EjecutarUnPaso();
    EXPECT_EQ(c2.ValorActual("x"), 0);

    Programa p3;
    p3.AgregarInstruccion("MAIN", Instruccion(30));
    p3.AgregarInstruccion("MAIN", Instruccion(oSub));
    p3.AgregarInstruccion("MAIN", Instruccion(oWrite, "x"));

    Calculadora c3(p3,"MAIN",20);
    c3.EjecutarUnPaso();
    c3.EjecutarUnPaso();
    c3.EjecutarUnPaso();
    EXPECT_EQ(c3.ValorActual("x"), -30);
}

TEST(test_calculadora, mult){
    Programa p1;
    p1.AgregarInstruccion("MAIN", Instruccion(30));
    p1.AgregarInstruccion("MAIN", Instruccion(10));
    p1.AgregarInstruccion("MAIN", Instruccion(oMul));
    p1.AgregarInstruccion("MAIN", Instruccion(oWrite, "x"));

    Calculadora c1(p1,"MAIN",20);
    c1.EjecutarUnPaso();
    c1.EjecutarUnPaso();
    c1.EjecutarUnPaso();
    c1.EjecutarUnPaso();
    EXPECT_EQ(c1.ValorActual("x"), 300);

    Programa p2;
    p2.AgregarInstruccion("MAIN", Instruccion(oMul));
    p2.AgregarInstruccion("MAIN", Instruccion(oWrite, "x"));

    Calculadora c2(p2,"MAIN",20);
    c2.EjecutarUnPaso();
    c2.EjecutarUnPaso();
    EXPECT_EQ(c2.ValorActual("x"), 0);

    Programa p3;
    p3.AgregarInstruccion("MAIN", Instruccion(30));
    p3.AgregarInstruccion("MAIN", Instruccion(oMul));
    p3.AgregarInstruccion("MAIN", Instruccion(oWrite, "x"));

    Calculadora c3(p3, "MAIN", 20);
    c3.EjecutarUnPaso();
    c3.EjecutarUnPaso();
    c3.EjecutarUnPaso();
    EXPECT_EQ(c3.ValorActual("x"), 0);
}


TEST(test_calculadora, ejecutar) {
    Programa p;
    p.AgregarInstruccion("MAIN", Instruccion(oRead, "x"));
    p.AgregarInstruccion("MAIN", Instruccion(2));
    p.AgregarInstruccion("MAIN", Instruccion(oAdd));
    p.AgregarInstruccion("MAIN", Instruccion(oWrite, "x"));

    Calculadora c(p,"MAIN",20);
    c.AsignarVariable("x", 38);
    c.EjecutarUnPaso();
    c.EjecutarUnPaso();
    c.EjecutarUnPaso();
    c.EjecutarUnPaso();
    EXPECT_EQ(c.ValorActual("x"), 40);
    c.EjecutarUnPaso();
    c.EjecutarUnPaso();
    c.EjecutarUnPaso();
    c.EjecutarUnPaso();
    EXPECT_EQ(c.ValorActual("x"), 42);
}
