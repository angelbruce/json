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
#include "e-json.h"

void log(JsonValue *v);

void logObj(JsonValueObj *o)
{
    if (!o)
        return;

    printf("\"%s\":", o->name);
    log(o->value);
    printf("\n");
    if (o->next)
    {
        printf(",");
        logObj(o->next);
    }
}

void logArray(JsonValueArray *o)
{
    if (!o)
        return;

    log(o->value);
    printf("\n");
    if (o->next)
    {
        printf(",");
        logArray(o->next);
    }
}

void log(JsonValue *v)
{
    switch (v->type)
    {
    case YT_STRING:
        printf("\"%s\"", v->val.sval);
        break;

    case YT_NUMBER:
        printf("%f", v->val.nval);
        break;

    case YT_BOOL:
        printf("%s", v->val.bval ? "true" : "false");
        break;

    case YT_NULL:
        printf("null");
        break;

    case YT_OBJECT:
        printf("{\n");
        logObj(v->val.oval);
        printf("}\n");
        break;

    case YT_ARRAY:
    {
        printf("[\n");
        logArray(v->val.aval);
        printf("]\n");
        break;
    }

    default:
        break;
    }
}

void parse(char *json)
{
    printf("------------------------------------------------------------------------------------------\n");
    JsonValue *jval = parse_json(json);
    printf("%d\n", jval->type);
    log(jval);
}


int main(int argc, char const *argv[])
{
    parse("{}");
    parse("{\"name\":\"zhangsan\",\"sex\":\"male\",\"age\":12,\"married\":false,\"hasBrother\":true,\"addr\":null}");
    parse("[]");
    parse("[1,2,3,4]");
    parse("[1,{},true,false,null]");
    parse("[\"图片\",1,true,false,null,{\"name\":\"zhangsan\",\"sex\":\"male\",\"age\":12,\"seq\":[1,{},{\"a\":true},\"3\",false],\"married\":false,\"hasBrother\":true,\"addr\":null}]");

    return 0;
}
