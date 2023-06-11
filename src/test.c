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

/// @brief
/// @param argc
/// @param argv
/// @return
int main(int argc, char const *argv[])
{
    parse("{}");
    parse("{\"name\":\"zhangsan\",\"sex\":\"male\",\"age\":12,\"married\":false,\"hasBrother\":true,\"addr\":null}");
    parse("[]");
    parse("[1,2,3,4]");
    parse("[1,{},true,false,null]");
    parse("[\"图片\",1,true,false,null,{\"name\":\"zhangsan\",\"sex\":\"male\",\"age\":12,\"seq\":[1,{},{\"a\":true},\"3\",false],\"married\":false,\"hasBrother\":true,\"addr\":null}]");
    // parse("{\"bundleData\":{\"bootstrappingRefs\": {\"vendor.js\":\"https://assets.msn.cn/bundles/v1/bingHomepage/latest/vendors.f5cbbb2bfe00cd654647.js\", \"microsoft.js\": \"https://assets.msn.cn/bundles/v1/bingHomepage/latest/microsoft.c5a59f142f9f409951d6.js\", \"common.js\":\"https://assets.msn.cn/bundles/v1/bingHomepage/latest/common.73635ce3dd2598d38c7f.js\", \"experience.js\":\"https://assets.msn.cn/bundles/v1/bingHomepage/latest/experience.ceb0bc63abd522f624d9.js\"}}, \"pcsData\": {\"info\": \"f:msnallexpusers,prg-sp-liveapi,platagyhp3cf,prg-cm-sopsp1,prg-cm-sopsp,weather4cf,prg-wea-staging,prg-1sw-imrsvtifpc,prg-1sw-rkctl,prg-cg-notif-center-cc,prg-1sw-cappr6,prg-1sw-cfmaskcb-t5,prg-1sw-cfmaskcb,prg-1sw-comspotstk,prg-1sw-comspotds,prg-1sw-comspots1,prg-1sw-comspott,prg-1sw-mebc10,prg-1sw-pnpsmbt,prg-1sw-pnpcmsf,prg-1sw-pnpcmss,prg-1sw-sosm,prg-1sw-ctlici,prg-cg-origplay,ac_homepage_t,prg-adspeek,prg-mbupsell-msg2,prg-cm-sopfi1,prg-cm-sopfi,1s-winauthservice,prg-1sw-textbtn3,prg-1sw-river-4r,prg-rrad-sticky,prg-pr2-rvsprofmigtrig,prg-pr2-bgrail,prg-1sw-dliconp3,prg-1sw-dlicon,prg-1sw-dliconp2,btie-bidlower-usa-t,btie-ta-p2a-t,prg-ias,1s-fcrypt,prg-wtch-angdpkc2,prg-1sw-vlidau10,prg-1sw-vlidauep,prg-pr2-waterfall,prg-pr2-dmcc135,prg-pr2-hrsexp2,prg-upsaip-w1-t,prg-wtch-mfm310,prg-upsaip-r-t,prg-wx-anmpr,prg-1sw-esprtpr-rv-c,prg-1sw-sacgrpc,prg-wx-sbn-vm,1s-rpssecautht,prg-1sw-p1wtrclm,prg-1sw-bnrcc,traffic-p2-comm-cta-cf,prg-p2-comm-cta-cf,traffic-tskb-p2-tlcf,prg-p2-inctp-empcf,prg-persfeed-c,prg-pr2-bnrdsms-c,prg-pr2-fbb-c,prg-1sw-cvrprg2-c,prg-intst-ad-pos-mix,prg-health-staging,prg-hotlistp1hu2c,prg-1sw-hotr2hu-c,prg-1sw-npetdgeo,prg-1sw-shtps,prg-hl-geo,prg-1sw-2cgmrow7,prg-pr2-bgcc-c,1s-xfm-control,1s-na-xfm-c,prg-pr2-sdrefresh,prg-pr2-v9cr3r6lt3usw,prg-pr2-lpv2tcap3s,prg-pr2-pcv9chreqs,prg-pr2-v9cr3r6lt3us,prg-pr2-spotify-c,1s-compicsync,ads-xandradfull,prg-1sw-otel,1s-defaultscn,prg-1sw-pde0,1s-defaultscnw,prg-1sw-tbrcounter,prg-ifprev,ads-stableidlookup,prg-sh-mhpcnny,prg-sh-cnnyh,prg-1sw-wxlfrc,prg-1sw-aqwd,prg-wx-dhgrd,1s-contview-obst,prg-1sw-entityperf,prg-entityperf,prg-1sw-srdus,prg-ugc-nosurvey,prg-1sw-xapgrid,prg-1unify1s,prg-unify1s,ads-obc-migr,prg-1s-cfnrtt,prg-1s-cfnrt,prg-vidcv1,1sakmigt,8d349501,ads-mgid-migr,prg-views-denh-c,prong1akmigt,prg-1sw-aqpn,prg-1s-wxxap,prg-sh-taxenabled,prg-ugc-cttsearch1,prg-1sw-wxprate,prg-enable-sw,prg-1sw-pollbart6,prg-1sw-ntf-pbar,prg-1sw-slpbwithoutwt,prg-share-rf2c,prg-sh-bdnews,prg-sh-unifyadd,prg-sh-usecpm,prg-ugc-videofeed1,prg-cg-notf2,prg-cg-notf,prg-ugc-cmsdocinfo,prg-wx-collid,prg-sh-3ds,prg-wxswstat,prg-1sw-bg-cookiec,prg-1sw-fdp2crs,1s-xapbnze,ads-xandrimpc-upgd,prg-wx-ani2hr,prg-upsunium-t,prg-nfstickypick,prg-use-edgeid-st-t2,prg-1s-edgeid,prg-ex-shopping,prg-wpo-swea,ads-cacheprst,ads-passbadv,prg-sh-atosgst,prg-akntpcrscncl,prg-ntp-wxncmbn,prg-sh-adstracking,prg-1sw-wxstm,prg-1sw-finbnd,prg-p2-aqv2,1s-brcvlightc,prg-ugc-feedfail,prg-mhs-msta1,prg-1sw-p2mebc10,prg-c-scrll-vir,prg-fin-explore,prg-1sw-finocn,prg-1sw-cfwxwind,prg-1sw-fimt2,prg-sh-cnmsnpn,prg-sh-cnmsnxapon,prg-sh-cnntpreco,prg-sh-mkton,prg-sh-ocon,prg-spr-egreco,prg-spr-enemktof,prg-spr-t-gmpgts,prg-wxwwb2uv2,prg-p2-aqv2glb,prg-sh-6j18d,prg-1sw-618,prg-pr2-jd618,prg-pr2-618,prg-sh-hp618,prg-sh-618jd,prg-sh-618tm,prg-pr2-railprod,prg-pr2-railmodelb,prg-sh-gzipxapcomp-c,prg-sh-bdanid,prg-1sw-secalertp1,prg-sh-rmitmlnk,prg-cg-nba-t,prg-cg-nba,prg-sh-bd-mit,prg-wea-artcsr,prg-wtchfeedwc,prg-sh-prngpersnw,prg-sh-eprore,prg-sh-prngpers,prg-spr-erfsurp,prg-spr-t-gsueg,prg-xandr-ar-no-pb,prg-xandr-w-no-pb,prg-p2-aqnbg;\", \"clientSettings\":{\"aid\":\"4C92635949214258BFE15B2911106FC3\", \"fd_muid\":\"3DC5E92C68926AA220BCFA0B69406B63\", \"static_page\":\"false\", \"queryparams\":\"?cm=zh-cn\", \"apptype\":\"bingHomepage\", \"pagetype\":\"widgetfeed\", \"configRootUrl\":\"https://assets.msn.com/config/v1/\", \"feedBaseDomain\":\"\", \"deviceFormFactor\":\"desktop\", \"pageGenTime\":\"2023-06-10T17:25:04Z\", \"pcsInfo\":{\"v\":\"20230607.7_master\", \"env\":\"prod\"}, \"locale\":{\"language\":\"zh\", \"market\":\"cn\", \"content\":{\"language\":\"zh\", \"market\":\"cn\"}, \"display\":{\"language\":\"zh\", \"market\":\"cn\"}}, \"featureFlags\":{}, \"market\":{ \"requestInput\":{ \"language\":\"zh\",\"region\":\"cn\", \"geo_country\":\"CN\"}, \"detection\":{ \"type\":\"compliance\",\"geo_country\":\"\"}}, \"servicesEndpoints\":{\"staticConfig\": {\"domain\": \"https://assets.msn.cn\", \"path\": \"/config/v3/\", \"v\": \"\"},\"crs\": {\"domain\": \"\", \"path\": \"/resolver/api/resolve/\", \"v\": \"v3\"},\"feedService\": {\"domain\": \"https://assets.msn.cn\", \"path\": \"\", \"v\": \"\"},\"enterpriseFeedService\": {\"domain\": \"https://ent-api.msn.com/\", \"path\": \"\", \"v\": \"\"}}, \"bundleInfo\":{\"v\":\"20230605.341\", \"alias\":\"latest\"}, \"os\":\"linux\", \"browser\":{\"browserType\":\"firefox\", \"version\":\"110\", \"ismobile\":\"false\"}, \"domain\":\"www.msn.cn\", \"detection\":{\"ip\":\"112.39.106.116\"}, \"geo_country\":\"CN\", \"geo_countryname\":\"China\", \"geo_subdivision\":\"Liaoning\", \"geo_zip\":\"110179\", \"geo_city\":\"Hunnan District\", \"geo_lat\":\"41.7315\", \"geo_long\":\"123.4753\", \"requestMuid\":\"3DC5E92C68926AA220BCFA0B69406B63\"}}}");

    return 0;
}
