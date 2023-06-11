Simple JSON Parser
* main types:
** JsonTokenType
** JsonToken
** JsonValueType
** JsonValue

* JsonTokenType can be:
** LT_LBP
** LT_RBP
** LT_LSQ
** LT_RSQ
** LT_COLON
** LT_COMMMA
** LT_STRING
** LT_NUMBER
** LT_TRUE
** LT_FALSE
** LT_NULL

* JsonValueType can be:
** YT_STRING
** YT_NUMBER
** YT_BOOL
** YT_ARRAY
** YT_OBJECT
** YT_NULL

*JsonValue canbe:
** string       char*
** number       number
** bool         ture/false (1/0)
** null         no value
** object       JsonValueObj 
** array        JsonValueArray
    