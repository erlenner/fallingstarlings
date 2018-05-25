// http://saadahmad.ca/cc-preprocessor-metaprogramming-basic-pattern-matching-macros-and-conditionals/
#define IF_1(true, ...) true
#define IF_0(true, ...) __VA_ARGS__
#define IF(value) CAT(IF_, value)

#define AND_11 EXISTS(1)
#define AND(x, y) TRY_EXTRACT_EXISTS ( CAT(CAT(AND_, x), y), 0 )

#define EAT(...)
#define EXPAND_TEST_EXISTS(...) EXPANDED, EXISTS(__VA_ARGS__) ) EAT (
#define GET_TEST_EXISTS_RESULT(x) ( CAT(EXPAND_TEST_, x),  DOESNT_EXIST )
 
#define GET_TEST_EXIST_VALUE_(expansion, existValue) existValue
#define GET_TEST_EXIST_VALUE(x) GET_TEST_EXIST_VALUE_  x 
 
#define TEST_EXISTS(x) GET_TEST_EXIST_VALUE (  GET_TEST_EXISTS_RESULT(x) )

#define DOES_VALUE_EXIST_EXISTS(...) 1
#define DOES_VALUE_EXIST_DOESNT_EXIST 0
#define DOES_VALUE_EXIST(x) CAT(DOES_VALUE_EXIST_, x)
 
#define EXTRACT_VALUE_EXISTS(...) __VA_ARGS__
#define EXTRACT_VALUE(value) CAT(EXTRACT_VALUE_, value)
 
#define TRY_EXTRACT_EXISTS(value, ...) \
    IF ( DOES_VALUE_EXIST(TEST_EXISTS(value)) )\
    ( EXTRACT_VALUE(value), __VA_ARGS__ )

#define AND_11 EXISTS(1)
#define AND(x, y) TRY_EXTRACT_EXISTS ( CAT(CAT(AND_, x), y), 0 )

#define OR_00 EXISTS(0)
#define OR(x, y) TRY_EXTRACT_EXISTS ( CAT(CAT(OR_, x), y), 1 )

#define XOR_01 EXISTS(1)
#define XOR_10 EXISTS(1)
#define XOR(x, y) TRY_EXTRACT_EXISTS ( CAT(CAT(XOR_, x), y), 0 )

#define NOT_0 EXISTS(1)
#define NOT(x) TRY_EXTRACT_EXISTS ( CAT(NOT_, x), 0 )

#define IS_ZERO_0 EXISTS(1)
#define IS_ZERO(x) TRY_EXTRACT_EXISTS ( CAT(IS_ZERO_, x), 0 )

#define IS_NOT_ZERO(x) NOT ( IS_ZERO(x) )

#define IS_ENCLOSED_TEST(...) EXISTS(1)
#define IS_ENCLOSED(x, ...) TRY_EXTRACT_EXISTS ( IS_ENCLOSED_TEST x, 0 )

#define ENCLOSE_EXPAND(...) EXPANDED, ENCLOSED, (__VA_ARGS__) ) EAT (
#define GET_CAT_EXP(a, b) (a, ENCLOSE_EXPAND b, DEFAULT, b )

#define CAT_WITH_ENCLOSED(a, b) a b
#define CAT_WITH_DEFAULT(a, b) a ## b
#define CAT_WITH(a, _, f, b) CAT_WITH_ ## f (a, b)

#define EVAL_CAT_WITH(...) CAT_WITH __VA_ARGS__
#define CAT(a, b) EVAL_CAT_WITH ( GET_CAT_EXP(a, b) )

#define EMPTY() 
#define DEFER(...) __VA_ARGS__ EMPTY()
#define DEFER2(...) __VA_ARGS__ DEFER(EMPTY) ()
#define DEFER3(...) __VA_ARGS__ DEFER2(EMPTY) ()
#define DEFER4(...) __VA_ARGS__ DEFER3(EMPTY) ()
#define DEFER5(...) __VA_ARGS__ DEFER4(EMPTY) ()

#define EVAL_1(...) __VA_ARGS__
#define EVAL_2(...) EVAL_1(EVAL_1(__VA_ARGS__))
#define EVAL_3(...) EVAL_2(EVAL_2(__VA_ARGS__))
#define EVAL_4(...) EVAL_3(EVAL_3(__VA_ARGS__))
#define EVAL_5(...) EVAL_4(EVAL_4(__VA_ARGS__))
#define EVAL_6(...) EVAL_5(EVAL_5(__VA_ARGS__))
#define EVAL_7(...) EVAL_6(EVAL_6(__VA_ARGS__))
#define EVAL_8(...) EVAL_7(EVAL_7(__VA_ARGS__))
#define EVAL(...) EVAL_8(__VA_ARGS__)

//#define EVAL2(...)  EVAL2_1(EVAL2_1(EVAL2_1(__VA_ARGS__)))
//#define EVAL2_1(...) EVAL2_2(EVAL2_2(EVAL2_2(__VA_ARGS__)))
//#define EVAL2_2(...) EVAL2_3(EVAL2_3(EVAL2_3(__VA_ARGS__)))
//#define EVAL2_3(...) EVAL2_4(EVAL2_4(EVAL2_4(__VA_ARGS__)))
//#define EVAL2_4(...) EVAL2_5(EVAL2_5(EVAL2_5(__VA_ARGS__)))
//#define EVAL2_5(...) __VA_ARGS__

#define HEAD(x, ...) x
#define TAIL(x, ...) __VA_ARGS__
 
#define TEST_LAST EXISTS(1)
#define IS_LIST_EMPTY(...) \
    TRY_EXTRACT_EXISTS( \
        DEFER(HEAD) (__VA_ARGS__ EXISTS(1))\
        , 0)
#define IS_LIST_NOT_EMPTY(...) NOT(IS_LIST_EMPTY(__VA_ARGS__))
 
#define ENCLOSE(...) ( __VA_ARGS__ )
#define REM_ENCLOSE_(...) __VA_ARGS__
#define REM_ENCLOSE(...) REM_ENCLOSE_ __VA_ARGS__
 
#define IF_ENCLOSED_1(true, ...) true
#define IF_ENCLOSED_0(true, ...) __VA_ARGS__
#define IF_ENCLOSED(...) CAT(IF_ENCLOSED_, IS_ENCLOSED(__VA_ARGS__))
#define OPT_REM_ENCLOSE(...) \
    IF_ENCLOSED (__VA_ARGS__) ( REM_ENCLOSE(__VA_ARGS__), __VA_ARGS__ )
 
// ARITHMETIC

#define INC_0 1
#define INC_1 2
#define INC_2 3
#define INC_3 4
#define INC_4 5
#define INC_5 6
#define INC_6 7
#define INC_7 8
#define INC_8 9
#define INC_9 10
#define INC_10 11
#define INC_11 12
#define INC_12 13
#define INC_13 14
#define INC_14 15
#define INC_15 16
#define INC_16 17
#define INC_17 18
#define INC_18 19
#define INC_19 20
#define INC_20 21
#define INC_21 22
#define INC_22 23
#define INC_23 24
#define INC_24 25
#define INC_25 26
#define INC_26 27
#define INC_27 28
#define INC_28 29
#define INC_29 30
#define INC_30 31
#define INC_31 32
#define INC_32 33
#define INC_33 34
#define INC_34 35
#define INC_35 36
#define INC_36 37
#define INC_37 38
#define INC_38 39
#define INC_39 40
#define INC_40 41
#define INC_41 42
#define INC_42 43
#define INC_43 44
#define INC_44 45
#define INC_45 46
#define INC_46 47
#define INC_47 48
#define INC_48 49
#define INC_49 50
#define INC_50 51
#define INC_51 52
#define INC_52 53
#define INC_53 54
#define INC_54 55
#define INC_55 56
#define INC_56 57
#define INC_57 58
#define INC_58 59
#define INC_59 60
#define INC_60 61
#define INC_61 62
#define INC_62 63
#define INC_63 64
#define INC_64 65
#define INC_65 66
#define INC_66 67
#define INC_67 68
#define INC_68 69
#define INC_69 70
#define INC_70 71
#define INC_71 72
#define INC_72 73
#define INC_73 74
#define INC_74 75
#define INC_75 76
#define INC_76 77
#define INC_77 78
#define INC_78 79
#define INC_79 80
#define INC_80 81
#define INC_81 82
#define INC_82 83
#define INC_83 84
#define INC_84 85
#define INC_85 86
#define INC_86 87
#define INC_87 88
#define INC_88 89
#define INC_89 90
#define INC_90 91
#define INC_91 92
#define INC_92 93
#define INC_93 94
#define INC_94 95
#define INC_95 96
#define INC_96 97
#define INC_97 98
#define INC_98 99
#define INC_99 100
#define INC_100 101
#define INC_101 102
#define INC_102 103
#define INC_103 104
#define INC_104 105
#define INC_105 106
#define INC_106 107
#define INC_107 108
#define INC_108 109
#define INC_109 110
#define INC_110 111
#define INC_111 112
#define INC_112 113
#define INC_113 114
#define INC_114 115
#define INC_115 116
#define INC_116 117
#define INC_117 118
#define INC_118 119
#define INC_119 120
#define INC_120 121
#define INC_121 122
#define INC_122 123
#define INC_123 124
#define INC_124 125
#define INC_125 126
#define INC_126 127
#define INC_127 0

#define INC(n) CAT(INC_, n)
 
#define DEC_1 0
#define DEC_2 1
#define DEC_3 2
#define DEC_4 3
#define DEC_5 4
#define DEC_6 5
#define DEC_7 6
#define DEC_8 7
#define DEC_9 8
#define DEC_10 9
#define DEC_11 10
#define DEC_12 11
#define DEC_13 12
#define DEC_14 13
#define DEC_15 14
#define DEC_16 15
#define DEC_17 16
#define DEC_18 17
#define DEC_19 18
#define DEC_20 19
#define DEC_21 20
#define DEC_22 21
#define DEC_23 22
#define DEC_24 23
#define DEC_25 24
#define DEC_26 25
#define DEC_27 26
#define DEC_28 27
#define DEC_29 28
#define DEC_30 29
#define DEC_31 30
#define DEC_32 31
#define DEC_33 32
#define DEC_34 33
#define DEC_35 34
#define DEC_36 35
#define DEC_37 36
#define DEC_38 37
#define DEC_39 38
#define DEC_40 39
#define DEC_41 40
#define DEC_42 41
#define DEC_43 42
#define DEC_44 43
#define DEC_45 44
#define DEC_46 45
#define DEC_47 46
#define DEC_48 47
#define DEC_49 48
#define DEC_50 49
#define DEC_51 50
#define DEC_52 51
#define DEC_53 52
#define DEC_54 53
#define DEC_55 54
#define DEC_56 55
#define DEC_57 56
#define DEC_58 57
#define DEC_59 58
#define DEC_60 59
#define DEC_61 60
#define DEC_62 61
#define DEC_63 62
#define DEC_64 63
#define DEC_65 64
#define DEC_66 65
#define DEC_67 66
#define DEC_68 67
#define DEC_69 68
#define DEC_70 69
#define DEC_71 70
#define DEC_72 71
#define DEC_73 72
#define DEC_74 73
#define DEC_75 74
#define DEC_76 75
#define DEC_77 76
#define DEC_78 77
#define DEC_79 78
#define DEC_80 79
#define DEC_81 80
#define DEC_82 81
#define DEC_83 82
#define DEC_84 83
#define DEC_85 84
#define DEC_86 85
#define DEC_87 86
#define DEC_88 87
#define DEC_89 88
#define DEC_90 89
#define DEC_91 90
#define DEC_92 91
#define DEC_93 92
#define DEC_94 93
#define DEC_95 94
#define DEC_96 95
#define DEC_97 96
#define DEC_98 97
#define DEC_99 98
#define DEC_100 99
#define DEC_101 100
#define DEC_102 101
#define DEC_103 102
#define DEC_104 103
#define DEC_105 104
#define DEC_106 105
#define DEC_107 106
#define DEC_108 107
#define DEC_109 108
#define DEC_110 109
#define DEC_111 110
#define DEC_112 111
#define DEC_113 112
#define DEC_114 113
#define DEC_115 114
#define DEC_116 115
#define DEC_117 116
#define DEC_118 117
#define DEC_119 118
#define DEC_120 119
#define DEC_121 120
#define DEC_122 121
#define DEC_123 122
#define DEC_124 123
#define DEC_125 124
#define DEC_126 125
#define DEC_127 126

#define DEC(n) CAT(DEC_, n)

#define ADD_INDIRECT() ADD_NO_EVAL
#define ADD_NO_EVAL(a, b) \
    IF ( IS_NOT_ZERO(b) ) ( \
        DEFER2 (ADD_INDIRECT) () (INC(a), DEC(b))\
        ,\
        a \
    )
#define ADD(a, b) EVAL(ADD_NO_EVAL(a, b))

#define SUBTRACT_INDIRECT() SUBTRACT_NO_EVAL
#define SUBTRACT_NO_EVAL(a, b) \
    IF ( IS_NOT_ZERO(b) ) ( \
        DEFER2 (SUBTRACT_INDIRECT) () (DEC(a), DEC(b))\
        ,\
        a \
    )
#define SUBTRACT(a, b) EVAL(SUBTRACT_NO_EVAL(a, b))

#define COMPARE_0(x) x
#define COMPARE_1(x) x
#define COMPARE_2(x) x
#define COMPARE_3(x) x
#define COMPARE_4(x) x
#define COMPARE_5(x) x
#define COMPARE_6(x) x
#define COMPARE_7(x) x
#define COMPARE_8(x) x
#define COMPARE_9(x) x
#define COMPARE_10(x) x
#define COMPARE_11(x) x
#define COMPARE_12(x) x
#define COMPARE_13(x) x
#define COMPARE_14(x) x
#define COMPARE_15(x) x
#define COMPARE_16(x) x
#define COMPARE_17(x) x
#define COMPARE_18(x) x
#define COMPARE_19(x) x
#define COMPARE_20(x) x
#define COMPARE_21(x) x
#define COMPARE_22(x) x
#define COMPARE_23(x) x
#define COMPARE_24(x) x
#define COMPARE_25(x) x
#define COMPARE_26(x) x
#define COMPARE_27(x) x
#define COMPARE_28(x) x
#define COMPARE_29(x) x
#define COMPARE_30(x) x
#define COMPARE_31(x) x
#define COMPARE_32(x) x
#define COMPARE_33(x) x
#define COMPARE_34(x) x
#define COMPARE_35(x) x
#define COMPARE_36(x) x
#define COMPARE_37(x) x
#define COMPARE_38(x) x
#define COMPARE_39(x) x
#define COMPARE_40(x) x
#define COMPARE_41(x) x
#define COMPARE_42(x) x
#define COMPARE_43(x) x
#define COMPARE_44(x) x
#define COMPARE_45(x) x
#define COMPARE_46(x) x
#define COMPARE_47(x) x
#define COMPARE_48(x) x
#define COMPARE_49(x) x
#define COMPARE_50(x) x
#define COMPARE_51(x) x
#define COMPARE_52(x) x
#define COMPARE_53(x) x
#define COMPARE_54(x) x
#define COMPARE_55(x) x
#define COMPARE_56(x) x
#define COMPARE_57(x) x
#define COMPARE_58(x) x
#define COMPARE_59(x) x
#define COMPARE_60(x) x
#define COMPARE_61(x) x
#define COMPARE_62(x) x
#define COMPARE_63(x) x
#define COMPARE_64(x) x
#define COMPARE_65(x) x
#define COMPARE_66(x) x
#define COMPARE_67(x) x
#define COMPARE_68(x) x
#define COMPARE_69(x) x
#define COMPARE_70(x) x
#define COMPARE_71(x) x
#define COMPARE_72(x) x
#define COMPARE_73(x) x
#define COMPARE_74(x) x
#define COMPARE_75(x) x
#define COMPARE_76(x) x
#define COMPARE_77(x) x
#define COMPARE_78(x) x
#define COMPARE_79(x) x
#define COMPARE_80(x) x
#define COMPARE_81(x) x
#define COMPARE_82(x) x
#define COMPARE_83(x) x
#define COMPARE_84(x) x
#define COMPARE_85(x) x
#define COMPARE_86(x) x
#define COMPARE_87(x) x
#define COMPARE_88(x) x
#define COMPARE_89(x) x
#define COMPARE_90(x) x
#define COMPARE_91(x) x
#define COMPARE_92(x) x
#define COMPARE_93(x) x
#define COMPARE_94(x) x
#define COMPARE_95(x) x
#define COMPARE_96(x) x
#define COMPARE_97(x) x
#define COMPARE_98(x) x
#define COMPARE_99(x) x
#define COMPARE_100(x) x
#define COMPARE_101(x) x
#define COMPARE_102(x) x
#define COMPARE_103(x) x
#define COMPARE_104(x) x
#define COMPARE_105(x) x
#define COMPARE_106(x) x
#define COMPARE_107(x) x
#define COMPARE_108(x) x
#define COMPARE_109(x) x
#define COMPARE_110(x) x
#define COMPARE_111(x) x
#define COMPARE_112(x) x
#define COMPARE_113(x) x
#define COMPARE_114(x) x
#define COMPARE_115(x) x
#define COMPARE_116(x) x
#define COMPARE_117(x) x
#define COMPARE_118(x) x
#define COMPARE_119(x) x
#define COMPARE_120(x) x
#define COMPARE_121(x) x
#define COMPARE_122(x) x
#define COMPARE_123(x) x
#define COMPARE_124(x) x
#define COMPARE_125(x) x
#define COMPARE_126(x) x
#define COMPARE_127(x) x

// END ARITHMETIC

// https://github.com/pfultz2/Cloak/wiki/C-Preprocessor-tricks,-tips,-and-idioms#deferred-expression
#define PRIMITIVE_CAT(a, ...) a ## __VA_ARGS__

#define OBSTRUCT(...) __VA_ARGS__ DEFER(EMPTY)()
#define EXPAND(...) __VA_ARGS__

#define COMPL(b) PRIMITIVE_CAT(COMPL_, b)
#define COMPL_0 1
#define COMPL_1 0

#define BOOL(x) COMPL(NOT(x))
#define IF2(c) IF(BOOL(c))

#define WHEN(c) IF2(c)(EXPAND, EAT)

#define BITAND(x) PRIMITIVE_CAT(BITAND_, x)
#define BITAND_0(y) 0
#define BITAND_1(y) y

#define CHECK_N(x, n, ...) n
#define CHECK(...) CHECK_N(__VA_ARGS__, 0,)
#define PROBE(x) x, 1,

#define IS_PAREN(x) CHECK(IS_PAREN_PROBE x)
#define IS_PAREN_PROBE(...) PROBE(~)



#define PRIMITIVE_COMPARE(x, y) IS_PAREN \
( \
COMPARE_ ## x ( COMPARE_ ## y) (())  \
)


#define IS_COMPARABLE(x) IS_PAREN( CAT(COMPARE_, x) (()) )

#define NOT_EQUAL(x, y) \
IF(BITAND(IS_COMPARABLE(x))(IS_COMPARABLE(y)) ) \
( \
   PRIMITIVE_COMPARE, \
   1 EAT \
)(x, y)

#define EQUAL(x, y) COMPL(NOT_EQUAL(x, y))




// FORMAT (search replace "FOR_EACH"):

#define FOR_EACH_INDIRECT() FOR_EACH_NO_EVAL
#define FOR_EACH_NO_EVAL(prefix, ...) \
    IF ( IS_LIST_NOT_EMPTY( __VA_ARGS__ )  ) \
    ( \
        prefix OPT_REM_ENCLOSE(HEAD(__VA_ARGS__); ) \
        DEFER2 ( FOR_EACH_INDIRECT ) () (prefix, TAIL(__VA_ARGS__)) \
    )
#define FOR_EACH(prefix, ...) \
    EVAL(FOR_EACH_NO_EVAL(prefix, __VA_ARGS__))


// Custom helpers:

#define STRIP(first, second) second

#define VICE(x, y, ...) y
#define VICE_TAIL(x, y, ...) __VA_ARGS__


// End Custom helpers



// DECLARE(extern, num1, num2, num3)
#define DECLARE_INDIRECT() DECLARE_NO_EVAL
#define DECLARE_NO_EVAL(prefix, ...) \
    IF ( IS_LIST_NOT_EMPTY( __VA_ARGS__ )  ) \
    ( \
        prefix OPT_REM_ENCLOSE(HEAD(__VA_ARGS__); ) \
        DEFER2 ( DECLARE_INDIRECT ) () (prefix, TAIL(__VA_ARGS__)) \
    )
#define DECLARE(prefix, ...) \
  EVAL(DECLARE_NO_EVAL(prefix, __VA_ARGS__))


//INIT_NAMESPACE_SHORT(Context, num1, num2, num3)
#define INIT_NAMESPACE_SHORT_INDIRECT() INIT_NAMESPACE_SHORT_NO_EVAL
#define INIT_NAMESPACE_SHORT_NO_EVAL(namespace_name, ...) \
    IF ( IS_LIST_NOT_EMPTY( __VA_ARGS__ )  ) \
    ( \
        namespace_name::HEAD(__VA_ARGS__) = HEAD(__VA_ARGS__); \
        DEFER2 ( INIT_NAMESPACE_SHORT_INDIRECT ) () (namespace_name, TAIL(__VA_ARGS__)) \
    )
#define INIT_NAMESPACE_SHORT(namespace_name, ...) \
    EVAL(INIT_NAMESPACE_SHORT_NO_EVAL(namespace_name, __VA_ARGS__))

//INIT_NAMESPACE(Context, int, num1, float*, num2, float, num3)
#define INIT_NAMESPACE_INDIRECT_DECLARATIONS() INIT_NAMESPACE_NO_EVAL_DECLARATIONS
#define INIT_NAMESPACE_NO_EVAL_DECLARATIONS(namespace_name, ...) \
    IF ( IS_LIST_NOT_EMPTY( __VA_ARGS__ )  ) \
    ( \
        HEAD(__VA_ARGS__) namespace_name::VICE(__VA_ARGS__); \
        DEFER2 ( INIT_NAMESPACE_INDIRECT_DECLARATIONS ) () (namespace_name, VICE_TAIL(__VA_ARGS__)) \
    )
#define INIT_NAMESPACE_INDIRECT_BODY() INIT_NAMESPACE_NO_EVAL_BODY
#define INIT_NAMESPACE_NO_EVAL_BODY(namespace_name, ...) \
    IF ( IS_LIST_NOT_EMPTY( __VA_ARGS__ )  ) \
    ( \
        namespace_name::VICE(__VA_ARGS__) = VICE(__VA_ARGS__); \
        DEFER2 ( INIT_NAMESPACE_INDIRECT_BODY ) () (namespace_name, VICE_TAIL(__VA_ARGS__)) \
    )
#define INIT_NAMESPACE_INDIRECT_PARAMETERS() INIT_NAMESPACE_NO_EVAL_PARAMETERS
#define INIT_NAMESPACE_NO_EVAL_PARAMETERS(...) \
    IF ( IS_LIST_NOT_EMPTY( __VA_ARGS__ )  ) \
    ( \
        HEAD(__VA_ARGS__) VICE(__VA_ARGS__) \
        IF ( IS_LIST_NOT_EMPTY( VICE_TAIL(__VA_ARGS__) ) ) \
        ( \
            OPT_REM_ENCLOSE(,) \
        ) \
        DEFER2 ( INIT_NAMESPACE_INDIRECT_PARAMETERS ) () (VICE_TAIL(__VA_ARGS__)) \
    )
#define INIT_NAMESPACE(namespace_name, ...) \
    EVAL(INIT_NAMESPACE_NO_EVAL_DECLARATIONS(namespace_name, __VA_ARGS__)) \
    void namespace_name::init(EVAL(INIT_NAMESPACE_NO_EVAL_PARAMETERS(__VA_ARGS__))){ \
    EVAL(INIT_NAMESPACE_NO_EVAL_BODY(namespace_name, __VA_ARGS__)) \
    }

//INIT_NAMESPACE_HEADER(Context, int, num1, float*, num2, float, num3)
#define INIT_NAMESPACE_HEADER_INDIRECT_DECLARATIONS() INIT_NAMESPACE_HEADER_NO_EVAL_DECLARATIONS
#define INIT_NAMESPACE_HEADER_NO_EVAL_DECLARATIONS(...) \
    IF ( IS_LIST_NOT_EMPTY( __VA_ARGS__ )  ) \
    ( \
        extern HEAD(__VA_ARGS__) VICE(__VA_ARGS__); \
        DEFER2 ( INIT_NAMESPACE_HEADER_INDIRECT_DECLARATIONS ) () (VICE_TAIL(__VA_ARGS__)) \
    )
#define INIT_NAMESPACE_HEADER_INDIRECT_BODY() INIT_NAMESPACE_HEADER_NO_EVAL_BODY
#define INIT_NAMESPACE_HEADER_NO_EVAL_BODY(...) \
    IF ( IS_LIST_NOT_EMPTY( __VA_ARGS__ )  ) \
    ( \
        VICE(__VA_ARGS__) = VICE(__VA_ARGS__); \
        DEFER2 ( INIT_NAMESPACE_HEADER_INDIRECT_BODY ) () (VICE_TAIL(__VA_ARGS__)) \
    )
#define INIT_NAMESPACE_HEADER_INDIRECT_PARAMETERS() INIT_NAMESPACE_HEADER_NO_EVAL_PARAMETERS
#define INIT_NAMESPACE_HEADER_NO_EVAL_PARAMETERS(...) \
    IF ( IS_LIST_NOT_EMPTY( __VA_ARGS__ )  ) \
    ( \
        HEAD(__VA_ARGS__) VICE(__VA_ARGS__) \
        IF ( IS_LIST_NOT_EMPTY( VICE_TAIL(__VA_ARGS__) ) ) \
        ( \
            OPT_REM_ENCLOSE(,) \
        ) \
        DEFER2 ( INIT_NAMESPACE_HEADER_INDIRECT_PARAMETERS ) () (VICE_TAIL(__VA_ARGS__)) \
    )
#define INIT_NAMESPACE_HEADER(namespace_name, ...) \
    namespace namespace_name{ \
        EVAL(INIT_NAMESPACE_HEADER_NO_EVAL_DECLARATIONS(__VA_ARGS__)) \
        void init(EVAL(INIT_NAMESPACE_HEADER_NO_EVAL_PARAMETERS(__VA_ARGS__))); \
    }

//INIT_STRUCT(Boid, int, num1, float*, num2, float, num3)
#define INIT_STRUCT_INDIRECT_BODY() INIT_STRUCT_NO_EVAL_BODY
#define INIT_STRUCT_NO_EVAL_BODY(...) \
    IF ( IS_LIST_NOT_EMPTY( __VA_ARGS__ )  ) \
    ( \
        this->VICE(__VA_ARGS__) = VICE(__VA_ARGS__); \
        DEFER2 ( INIT_STRUCT_INDIRECT_BODY ) () (VICE_TAIL(__VA_ARGS__)) \
    )
#define INIT_STRUCT_INDIRECT_PARAMETERS() INIT_STRUCT_NO_EVAL_PARAMETERS
#define INIT_STRUCT_NO_EVAL_PARAMETERS(...) \
    IF ( IS_LIST_NOT_EMPTY( __VA_ARGS__ )  ) \
    ( \
        HEAD(__VA_ARGS__) VICE(__VA_ARGS__) \
        IF ( IS_LIST_NOT_EMPTY( VICE_TAIL(__VA_ARGS__) ) ) \
        ( \
            OPT_REM_ENCLOSE(,) \
        ) \
        DEFER2 ( INIT_STRUCT_INDIRECT_PARAMETERS ) () (VICE_TAIL(__VA_ARGS__)) \
    )
#define INIT_STRUCT(struct_name, ...) \
    void struct_name::init(EVAL(INIT_STRUCT_NO_EVAL_PARAMETERS(__VA_ARGS__))){ \
    EVAL(INIT_STRUCT_NO_EVAL_BODY(__VA_ARGS__)) \
    }
 
//INIT_CLASS(Boid, int, num1, float*, num2, float, num3)
#define INIT_CLASS_INDIRECT_INIT_LIST() INIT_CLASS_NO_EVAL_INIT_LIST
#define INIT_CLASS_NO_EVAL_INIT_LIST(...) \
    IF ( IS_LIST_NOT_EMPTY( __VA_ARGS__ )  ) \
    ( \
        VICE(__VA_ARGS__)(VICE(__VA_ARGS__)) \
        IF ( IS_LIST_NOT_EMPTY( VICE_TAIL(__VA_ARGS__) ) ) \
        ( OPT_REM_ENCLOSE(,) ) \
        DEFER2 ( INIT_CLASS_INDIRECT_INIT_LIST ) () (VICE_TAIL(__VA_ARGS__)) \
    )
#define INIT_CLASS_INDIRECT_PARAMETERS() INIT_CLASS_NO_EVAL_PARAMETERS
#define INIT_CLASS_NO_EVAL_PARAMETERS(...) \
    IF ( IS_LIST_NOT_EMPTY( __VA_ARGS__ )  ) \
    ( \
        HEAD(__VA_ARGS__) VICE(__VA_ARGS__) \
        IF ( IS_LIST_NOT_EMPTY( VICE_TAIL(__VA_ARGS__) ) ) \
        ( OPT_REM_ENCLOSE(,) ) \
        DEFER2 ( INIT_CLASS_INDIRECT_PARAMETERS ) () (VICE_TAIL(__VA_ARGS__)) \
    )
#define INIT_CLASS(CLASS_name, ...) \
    void CLASS_name::init(EVAL(INIT_CLASS_NO_EVAL_PARAMETERS(__VA_ARGS__))) : \
    EVAL(INIT_CLASS_NO_EVAL_INIT_LIST(__VA_ARGS__)) \
    {}


// #define M(i, _) case i: b = i; break;
// EVAL(RANGE(M, 3, 8))
#define RANGE(macro, start, end, ...) \
    WHEN(NOT_EQUAL(start, end)) \
    ( \
        OBSTRUCT(RANGE_INDIRECT) () \
        ( \
            macro, start, DEC(end), __VA_ARGS__ \
        ) \
        OBSTRUCT(macro) \
        ( \
            DEC(end), __VA_ARGS__ \
        ) \
    )
#define RANGE_INDIRECT() RANGE
