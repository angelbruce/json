#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _json_lex_token_ JsonToken;
typedef struct _json_value_ JsonValue;
typedef struct _json_value_obj_ JsonValueObj;
typedef struct _json_value_array_ JsonValueArray;

typedef enum _json_lex_token_type_
{
    LT_LBP,
    LT_RBP,
    LT_LSQ,
    LT_RSQ,
    LT_COLON,
    LT_COMMMA,
    LT_STRING,
    LT_NUMBER,
    LT_TRUE,
    LT_FALSE,
    LT_NULL
} JsonTokenType;

typedef struct _json_lex_token_
{
    JsonTokenType type;
    char *value;
    int len;

    JsonToken *prev;
    JsonToken *next;
} JsonToken;

typedef enum _json_value_type_
{
    YT_STRING,
    YT_NUMBER,
    YT_BOOL,
    YT_ARRAY,
    YT_OBJECT,
    YT_NULL
} JsonValueType;

typedef struct _json_value_
{
    JsonValueType type;
    union
    {
        JsonValueObj *oval;
        JsonValueArray *aval;
        char *sval;
        double nval;
        short bval;
    } val;

} JsonValue;

typedef struct _json_value_obj_
{
    char *name;
    JsonValue *value;

    JsonValueObj *prev;
    JsonValueObj *next;
} JsonValueObj;

typedef struct _json_value_array_
{
    JsonValue *value;

    JsonValueArray *prev;
    JsonValueArray *next;
} JsonValueArray;

JsonValue *parse_json(char *stream);
JsonToken *parse_json_token(char *stream);
JsonValue *parse_json_value(JsonToken **cur);