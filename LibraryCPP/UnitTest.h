/****************************** Module Header ******************************\
Filename:		MyUnitTest.h
Project:		Vonng::Matlab
Digest:			Simple Unit Test Framework
Author:			Feng Ruohang
Create:			2014/11/26 22:36
LastModify:		2014/11/26 22:36
\****************************** Module Header ******************************/

/****************************Usage********************************\
TEST_CASE(CaseName)
{
    TestStatement;
    TEST_ASSERTs(expression);
}
\*****************************Usage*******************************/


//TEST_ASSERT(Expression)
#define TEST_ASSERT(e) do{if(!(e))throw "Ops!";}while(0)
#define ASSERT(e) do{if(!(e))throw "Ops!";}while(0)
#define ASSERT_EQ(a,b) do{if(!((a) == (b)))throw "Ops!";}while(0)
#define ASSERT_NE(a,b) do{if(!((a) != (b)))throw "Ops!";}while(0)
#define ASSERT_LE(a,b) do{if(!((a) <= (b)))throw "Ops!";}while(0)
#define ASSERT_GE(a,b) do{if(!((a) >= (b)))throw "Ops!";}while(0)
#define ASSERT_L(a,b) do{if(!((a) < (b)))throw "Ops!";}while(0)
#define ASSERT_G(a,b) do{if(!((a) > (b)))throw "Ops!";}while(0)

//Test_CASE
#define TEST_CASE(NAME)                                            \
         extern void TESTCASE_##NAME();                             \
         namespace vonng_unittest									\
         {                                                          \
             class TESTCASE_RUNNER_##NAME                           \
             {                                                      \
             public:                                                \
                 TESTCASE_RUNNER_##NAME()                           \
                 {                                                  \
                     TESTCASE_##NAME();                             \
                 }                                                  \
             } TESTCASE_RUNNER_##NAME##_INSTANCE;                   \
         }                                                          \
         void TESTCASE_##NAME()

