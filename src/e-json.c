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

int JSON_TEMP_INDEX = 0;
#define Var(T,var,n)                T *var  = (T *) malloc(sizeof(T) * (n)); memset(var,0,sizeof(T) * (n));
#define New(T,var,n)                var  = (T *) malloc(sizeof(T) * (n)); memset(var,0,sizeof(T) * (n));
#define NewToken(var,t,l)           Var(JsonToken,var,1); var->len=1; var->type=t; var->len=l;
#define AppendToken(head,cur,token) if(!cur) { head = cur = token; } else { cur->next=token; token->prev=cur; cur=token;} 
#define AppendValue(cur,value)      if(!cur) { cur = value; } else { cur->next=value; value->prev=cur; cur=value;}
#define Newstr(var,raw,len)         Var(char,var,len+1);  for(JSON_TEMP_INDEX =0;JSON_TEMP_INDEX < len; JSON_TEMP_INDEX ++) var[JSON_TEMP_INDEX] = raw[JSON_TEMP_INDEX];                                        
#define Next(cur)                   *cur = (*cur) -> next;

JsonValue *parse_json(char *stream)
{
    JsonToken *tokens = parse_json_token(stream);
    return parse_json_value(&tokens);
}

JsonToken *parse_json_token(char *stream)
{
    if (!stream)
    {
        return NULL;
    }

    char *pos = stream;
    JsonToken *cur = NULL, *head = NULL;
    int i = 0;
    while (pos && *pos != '\0')
    {
        char c = *pos;
        if (c == ' ' || c == '\t' || c == '\f' || c == '\r' || c == '\n')
        {
            pos++;
        }
        else if (c == '{')
        {
            NewToken(token, LT_LBP, 1);
            token->value = pos;
            AppendToken(head, cur, token);
            pos++;
        }
        else if (c == '}')
        {
            NewToken(token, LT_RBP, 1);
            token->value = pos;
            AppendToken(head, cur, token);
            pos++;
        }
        else if (c == '[')
        {
            NewToken(token, LT_LSQ, 1);
            token->value = pos;
            pos++;
            AppendToken(head, cur, token);
        }
        else if (c == ']')
        {
            NewToken(token, LT_RSQ, 1);
            token->value = pos;
            AppendToken(head, cur, token);
            pos++;
        }
        else if (c == ':')
        {
            NewToken(token, LT_COLON, 1);
            token->value = pos;
            AppendToken(head, cur, token);
            pos++;
        }
        else if (c == ',')
        {
            NewToken(token, LT_COMMMA, 1);
            token->value = pos;
            AppendToken(head, cur, token);
            pos++;
        }
        else if (c == '-' || (c >= '0' && c <= '9') || c == '.')
        {
            NewToken(token, LT_NUMBER, 1);
            token->value = pos;
            char *k = pos;
            do
            {
                pos++;
                c = *pos;
            } while (pos && (c == '-' || c == '+' || c == '.' || c == 'E' || (c >= '0' && c <= '9')));
            int len = (size_t)pos - (size_t)k;
            token->len = len;
            AppendToken(head, cur, token);
        }
        else if (c == 't')
        {
            NewToken(token, LT_TRUE, 4);
            token->value = pos;
            do
            {
                pos++;
                c = *pos;
            } while (pos && (c == 'r' || c == 'u' || c == 'e'));
            AppendToken(head, cur, token);
        }
        else if (c == 'f')
        {
            NewToken(token, LT_FALSE, 5);
            token->value = pos;
            do
            {
                pos++;
                c = *pos;
            } while (pos && (c == 'a' || c == 'l' || c == 's' || c == 'e'));
            AppendToken(head, cur, token);
        }
        else if (c == 'n')
        {
            NewToken(token, LT_NULL, 4);
            token->value = pos;
            do
            {
                pos++;
                c = *pos;
            } while (pos && (c == 'u' || c == 'l' || c == 'u'));
            AppendToken(head, cur, token);
        }
        else if (c == '\"')
        {
            NewToken(token, LT_STRING, 1);
            token->value = pos;
            char *k = pos;
            do
            {
                pos++;
                c = *pos;
            } while ((*pos != '\0') && c != '\"' && (*(pos - 1)) != '\\');
            pos++;
            int len = (size_t)pos - (size_t)k;
            token->len = len;
            AppendToken(head, cur, token);
        }
        else
        {
            printf("error lex json found %s\n", pos);
            pos = 0;
            break;
        }
    }

    return head;
}

JsonValue *parse_json_value(JsonToken **cur)
{
    if (!cur || !(*cur))
    {
        return NULL;
    }

    switch ((*cur)->type)
    {
    case LT_STRING:
    {
        Var(JsonValue, str, 1);
        str->type = YT_STRING;
        Newstr(val, ((*cur)->value + 1), ((*cur)->len) - 2);
        str->val.sval = val;
        Next(cur);
        return str;
        break;
    }
    case LT_NUMBER:
    {
        Var(JsonValue, dval, 1);
        dval->type = YT_NUMBER;
        Newstr(val, (*cur)->value, (*cur)->len);
        dval->val.nval = atof(val);
        Next(cur);
        return dval;
        break;
    }
    case LT_TRUE:
    {
        Var(JsonValue, bval, 1);
        bval->type = YT_BOOL;
        bval->val.bval = 1;
        Next(cur);
        return bval;
        break;
    }
    case LT_FALSE:
    {
        Var(JsonValue, bval, 1);
        bval->type = YT_BOOL;
        bval->val.bval = 0;
        Next(cur);
        return bval;
        break;
    }
    case LT_NULL:
    {
        Var(JsonValue, nval, 1);
        nval->type = YT_NULL;
        Next(cur);
        return nval;
        break;
    }
    case LT_LBP:
    {
        Var(JsonValue, jval, 1);
        Var(JsonValueObj, oval, 1);
        jval->type = YT_OBJECT;
        jval->val.oval = oval;
        Next(cur);
        while ((*cur) && (*cur)->type != LT_RBP)
        {
            if ((*cur)->type == LT_COMMMA)
            {
                Next(cur);
            }

            Newstr(val, ((*cur)->value + 1), ((*cur)->len - 2));
            oval->name = val;
            Next(cur);
            Next(cur);
            oval->value = parse_json_value(cur);
            Var(JsonValueObj, next, 1);
            oval->next = next;
            next->prev = oval;
            oval = next;
        };

        if (oval->prev)
            oval->prev->next = 0;
        else
            jval->val.oval = 0;
        oval->prev = 0;
        free(oval);

        Next(cur);
        return jval;
        break;
    }
    case LT_LSQ:
    {
        Var(JsonValue, jval, 1);
        Var(JsonValueArray, aval, 1);
        jval->type = YT_ARRAY;
        jval->val.aval = aval;
        Next(cur);

        while ((*cur) && (*cur)->type != LT_RSQ)
        {
            if ((*cur)->type == LT_COMMMA)
            {
                Next(cur);
            }

            aval->value = parse_json_value(cur);
            Var(JsonValueArray, next, 1);
            aval->next = next;
            next->prev = aval;
            aval = next;
        };

        if (aval->prev)
            aval->prev->next = 0;
        else
            jval->val.aval = 0;
        aval->prev = 0;
        free(aval);
        Next(cur);
        return jval;
        break;
    }
    default:
    {
        printf("error parse json found %s\n", (*cur)->value);
        *cur = 0;
        break;
    }
    }
}
