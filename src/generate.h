#define IF_1(true, ...) true
#define IF_0(true, ...) __VA_ARGS__
#define IF(value) CAT(IF_, value)

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
 
#define NOT_0 EXISTS(1)
#define NOT(x) TRY_EXTRACT_EXISTS ( CAT(NOT_, x), 0 )
 
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
