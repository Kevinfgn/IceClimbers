//
// Created by randall.guzman on 23/11/2019.
//

#include "ICE-Json.h"
#include <stdio.h>
#include <json-c/json.h>

/*@Parameters Array char
 * JsonParser lee y convierte a JsonObject
 * */

struct json_object * jsonParserPlayer(char jsonString[]) {

    /*
     * Struct para guardar los Json del jugador
     */

    struct json_object *parsed_json;
    struct json_object *posX;
    struct json_object *posY;
    struct json_object *attack;
    struct json_object *lives;

    parsed_json = json_tokener_parse(jsonString);

    //Extrae la informacion
    json_object_object_get_ex(parsed_json,"posX",&posX);
    json_object_object_get_ex(parsed_json,"posY",&posY);
    json_object_object_get_ex(parsed_json,"attack",&attack);
    json_object_object_get_ex(parsed_json,"lives",&lives);

    return parsed_json;

}

const char *jsonWriterPlayer(int posX,int posY, int attack, int lives){

    //Crea nuevo json
    json_object *jsonObject=json_object_new_object();
    json_object *jsonObjectPopo=json_object_new_object();

    //Crea la data del Json
    json_object *jsonPosX=json_object_new_int(posX);
    json_object *jsonPosY=json_object_new_int(posY);
    json_object *jsonAttack=json_object_new_int(attack);
    json_object *jsonLives=json_object_new_int(lives);

    //Anade la data al Json
    json_object_object_add(jsonObjectPopo,"posX",jsonPosX);
    json_object_object_add(jsonObjectPopo,"posY",jsonPosY);
    json_object_object_add(jsonObjectPopo,"attack",jsonAttack);
    json_object_object_add(jsonObjectPopo,"lives",jsonLives);
    printf(json_object_to_json_string(jsonObjectPopo));
    return json_object_to_json_string(jsonObject);

}


