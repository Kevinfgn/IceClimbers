//
// Created by aaron on 23/11/19.
//

#ifndef CLIENT_ICE_JSON_H
#define CLIENT_ICE_JSON_H

struct json_object * jsonParser(char jsonString[]);
const char *jsonWriterPlayer(int posX,int posY, int attack, int lives);



#endif //CLIENT_ICE_JSON_H
