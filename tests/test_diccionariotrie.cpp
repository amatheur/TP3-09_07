#include "../src/DiccionarioTrie.h"


#include <gtest/gtest.h>


TEST(diccionarioTrie_test, vacio) {
    DiccionarioTrie<int> vacio;

    EXPECT_EQ(vacio.Definido("hola"), 0);
}

TEST(diccionarioTrie_test, asignar) {
    DiccionarioTrie<int> singleton;
    singleton.Definir("hola", 1);

    EXPECT_EQ(singleton.Significado("hola"), 1);
}

TEST(diccionarioTrie_test, obtener) {
    DiccionarioTrie<int> sin_prefijos;
    DiccionarioTrie<int> con_prefijos;

    sin_prefijos.Definir("hola", 1);
    sin_prefijos.Definir("chau", 2);
    sin_prefijos.Definir("adios", 3);

    con_prefijos.Definir("c", 1);
    con_prefijos.Definir("casa", 2);
    con_prefijos.Definir("casona",3);

    EXPECT_EQ(sin_prefijos.Significado("hola"), 1);
    EXPECT_EQ(sin_prefijos.Significado("chau"), 2);
    EXPECT_EQ(sin_prefijos.Significado("adios"), 3);

    EXPECT_EQ(con_prefijos.Significado("c"), 1);
    EXPECT_EQ(con_prefijos.Significado("casa"), 2);
    EXPECT_EQ(con_prefijos.Significado("casona"), 3);
}

TEST(diccionarioTrie_test, iteradores) {
    DiccionarioTrie<int> con_prefijos;


    con_prefijos.Definir("c", 1);
    con_prefijos.Definir("casa", 2);
    con_prefijos.Definir("casona",3);

    DiccionarioTrie<int>::ItDiccTrie it = con_prefijos.CrearIt();
    EXPECT_EQ(get<1>(it.Actual()), 1);

    it.Avanzar();
    EXPECT_EQ(get<1>(it.Actual()), 2);

    it.Avanzar();

    EXPECT_EQ(get<1>(it.Actual()), 3);
}
/*
TEST(diccionarioTrie_test, count) {
    DiccionarioTrie<int> vacio;
    DiccionarioTrie<int> sin_prefijos;
    DiccionarioTrie<int> con_prefijos;

    sin_prefijos["hola"] = 1;
    sin_prefijos["chau"] =
    sin_prefijos["adios"] =  3;

    con_prefijos["c"] =  1;
    con_prefijos["casa"] =  2;
    con_prefijos["casona"] =  3;

    EXPECT_FALSE(vacio.count("a") == 1);
    EXPECT_FALSE(vacio.count("aaaa") == 1);
    EXPECT_FALSE(vacio.count("adios") == 1);

    EXPECT_TRUE(sin_prefijos.count("hola") == 1);
    EXPECT_TRUE(sin_prefijos.count("chau") == 1);
    EXPECT_TRUE(sin_prefijos.count("adios") == 1);

    EXPECT_FALSE(sin_prefijos.count("h") == 1);
    EXPECT_FALSE(sin_prefijos.count("ho") == 1);
    EXPECT_FALSE(sin_prefijos.count("hol") == 1);

    EXPECT_TRUE(con_prefijos.count("c") == 1);
    EXPECT_TRUE(con_prefijos.count("casa") == 1);
    EXPECT_TRUE(con_prefijos.count("casona") == 1);
    EXPECT_FALSE(con_prefijos.count("ca") == 1);
    EXPECT_FALSE(con_prefijos.count("cas") == 1);
    EXPECT_FALSE(con_prefijos.count("caso") == 1);
}

TEST(diccionarioTrie_test, copiar) {
    DiccionarioTrie<int> sin_prefijos;
    DiccionarioTrie<int> con_prefijos;

    sin_prefijos["hola"] = 1;
    sin_prefijos["chau"] = 2;
    sin_prefijos["adios"] =  3;

    con_prefijos["c"] =  1;
    con_prefijos["casa"] =  2;
    con_prefijos["casona"] =  3;

    DiccionarioTrie<int> copia(sin_prefijos);

    EXPECT_TRUE(copia.count("hola") == 1);
    EXPECT_TRUE(copia.count("chau") == 1);
    EXPECT_TRUE(copia.count("adios") == 1);

    EXPECT_FALSE(copia.count("h") == 1);
    EXPECT_FALSE(copia.count("ho") == 1);
    EXPECT_FALSE(copia.count("hol") == 1);

    EXPECT_EQ(sin_prefijos["hola"], copia["hola"]);
    EXPECT_EQ(sin_prefijos["chau"], copia["chau"]);
    EXPECT_EQ(sin_prefijos["adios"], copia["adios"]);

    DiccionarioTrie<int> copia2(con_prefijos);

    EXPECT_TRUE(copia2.count("c") == 1);
    EXPECT_TRUE(copia2.count("casa") == 1);
    EXPECT_TRUE(copia2.count("casona") == 1);
    EXPECT_FALSE(copia2.count("ca") == 1);
    EXPECT_FALSE(copia2.count("cas") == 1);
    EXPECT_FALSE(copia2.count("caso") == 1);

    EXPECT_EQ(copia2["c"], 1);
    EXPECT_EQ(copia2["casa"], 2);
    EXPECT_EQ(copia2["casona"], 3);
}

TEST(diccionarioTrie_test, no_aliasing) {
    DiccionarioTrie<int> singleton;
    singleton["hola"] = 1;

    DiccionarioTrie<int> copia(singleton);
    copia["hare"] =  2;
    ASSERT_FALSE(singleton.count("hare") == 1);
}

TEST(diccionarioTrie_test, no_aliasing_erase) {
    DiccionarioTrie<int> singleton;
    singleton["hola"] = 1;

    DiccionarioTrie<int> copia(singleton);
    copia["hare"] =  2;
    copia.erase("hola");
    ASSERT_FALSE(singleton.count("hare") == 1);
    EXPECT_EQ(singleton.count("hola"), 1);
    EXPECT_EQ(singleton.at("hola"), 1);
}


TEST(diccionarioTrie_test, no_aliasing_erase_2) {
    DiccionarioTrie<int> singleton;
    singleton["hola"] = 1;

    DiccionarioTrie<int> copia(singleton);
    copia["hare"] =  2;
    singleton.erase("hola");
    ASSERT_FALSE(singleton.count("hare") == 1);
    EXPECT_EQ(copia.count("hola"), 1);
    EXPECT_EQ(copia.at("hola"), 1);
}

TEST(diccionarioTrie_test, TrieDeTries) {
    DiccionarioTrie<int> vacio;
    DiccionarioTrie<int> singleton;
    DiccionarioTrie<int> sin_prefijos;
    DiccionarioTrie<int> con_prefijos;
    DiccionarioTrie<DiccionarioTrie<int>> dicc_dicc;

    singleton["hola"] = 1;

    sin_prefijos["hola"] = 1;
    sin_prefijos["chau"] = 2;
    sin_prefijos["adios"] =  3;

    con_prefijos["c"] =  1;
    con_prefijos["casa"] =  2;
    con_prefijos["casona"] =  3;

    dicc_dicc["vacio"] =  vacio;
    dicc_dicc["singleton"] =  singleton;
    dicc_dicc["sin_prefijos"] =  sin_prefijos;
    dicc_dicc["con_prefijos"] =  con_prefijos;

    EXPECT_FALSE(dicc_dicc["vacio"].count("hola") == 1);

    EXPECT_EQ(dicc_dicc["singleton"]["hola"], 1);

    EXPECT_EQ(dicc_dicc["sin_prefijos"]["hola"], 1);
    EXPECT_EQ(dicc_dicc["sin_prefijos"]["chau"], 2);
    EXPECT_EQ(dicc_dicc["sin_prefijos"]["adios"], 3);

    EXPECT_EQ(dicc_dicc["con_prefijos"]["c"], 1);
    EXPECT_EQ(dicc_dicc["con_prefijos"]["casa"], 2);
    EXPECT_EQ(dicc_dicc["con_prefijos"]["casona"], 3);

}

TEST(diccionarioTrie_test, eraseUnicaClave) {
    DiccionarioTrie<int> singleton;
    singleton["hola"] = 1;

    EXPECT_TRUE(singleton.count("hola") == 1);

    singleton.erase("hola");

    EXPECT_FALSE(singleton.count("hola") == 1);
}

TEST(diccionarioTrie_test, claveVacia) {
    DiccionarioTrie<int> singleton;
    singleton[""] = 1;

    EXPECT_TRUE(singleton.count("") == 1);

    singleton.erase("");

    EXPECT_FALSE(singleton.count("") == 1);
}


TEST(diccionarioTrie_test, erase) {
    DiccionarioTrie<int> sin_prefijos;
    DiccionarioTrie<int> con_prefijos;

    sin_prefijos["hola"] = 1;
    sin_prefijos["chau"] = 2;
    sin_prefijos["adios"] =  3;

    con_prefijos["c"] =  1;
    con_prefijos["casa"] =  2;
    con_prefijos["casona"] =  3;

    con_prefijos.erase("c");
    EXPECT_FALSE(con_prefijos.count("c") == 1);

    EXPECT_TRUE(con_prefijos.count("casa") == 1);
    EXPECT_TRUE(con_prefijos.count("casona") == 1);

    con_prefijos.erase("casona");
    EXPECT_FALSE(con_prefijos.count("casona") == 1);

    EXPECT_TRUE(con_prefijos.count("casa") == 1);

    con_prefijos.erase("casa");
    EXPECT_FALSE(con_prefijos.count("casa") == 1);

    sin_prefijos.erase("hola");
    EXPECT_FALSE(sin_prefijos.count("hola") == 1);

    sin_prefijos.erase("chau");
    EXPECT_FALSE(sin_prefijos.count("chau") == 1);

    sin_prefijos.erase("adios");
    EXPECT_FALSE(sin_prefijos.count("adios") == 1);
}
*/

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

