/**
MIT License

Copyright (c) 2023 angelbruce

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _json_lex_token_ JsonToken;
typedef struct _json_value_ JsonValue;
typedef struct _json_value_obj_ JsonValueObj;
typedef struct _json_value_array_ JsonValueArray;

/**
 * json token type for lexer parse
*/
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

/**
 * json token parsed by lex parser
*/
typedef struct _json_lex_token_
{
    JsonTokenType type;
    char *value;
    int len;

    JsonToken *prev;
    JsonToken *next;
} JsonToken;

/**
 * json value type for syntax parse
*/
typedef enum _json_value_type_
{
    YT_STRING,
    YT_NUMBER,
    YT_BOOL,
    YT_ARRAY,
    YT_OBJECT,
    YT_NULL
} JsonValueType;

/**
 * json value parsed by syntax parser
*/
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

/**
 * json object {}
*/
typedef struct _json_value_obj_
{
    char *name;
    JsonValue *value;

    JsonValueObj *prev;
    JsonValueObj *next;
} JsonValueObj;

/**
 * json array []
*/
typedef struct _json_value_array_
{
    JsonValue *value;

    JsonValueArray *prev;
    JsonValueArray *next;
} JsonValueArray;

/**
 * parse json stream and return the parsed JsonValue result.
*/
JsonValue *parse_json(char *stream);
/**
 * parse json stream and return the lexer token stream.
*/
JsonToken *parse_json_token(char *stream);
/**
 * parse json token stream and return the parsed JsonValue result.
*/
JsonValue *parse_json_value(JsonToken **cur);
