Simple JSON Parser

      JsonValue *json = parse_json("{}");
      

* main types:
1. JsonTokenType
1. JsonToken
1. JsonValueType
1. JsonValue

* JsonTokenType can be:
1. LT_LBP
1. LT_RBP
1. LT_LSQ
1. LT_RSQ
1. LT_COLON
1. LT_COMMMA
1. LT_STRING
1. LT_NUMBER
1. LT_TRUE
1. LT_FALSE
1. LT_NULL

* JsonValueType can be:
1. YT_STRING
1. YT_NUMBER
1. YT_BOOL
1. YT_ARRAY
1. YT_OBJECT
1. YT_NULL

*JsonValue canbe:
1. string       char*
1. number       number
1. bool         ture/false (1/0)
1. null         no value
1. object       JsonValueObj 
1. array        JsonValueArray
    
