#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/bitmap.h>
#include <stdio.h>
#define ScreenWidth 800
#define  ScreenHeight 600
int distancia_max=0;
//definicion de la matriz de bloques
//int popo[]
int focas[12][2]={{2,1,0},{-99,-99,0},{-99,-99,0},{-99,-99,0},{-99,-99,0},{-99,-99,0},{-99,-99,0},{-99,-99,0},{-99,-99,0},{-99,-99,0},{-99,-99,0},{-99,-99,0}};
int pajaros[12][2];
int hielos[12][2];
int bloques[8][9]={{1,1,1,1,1,1,1,1,1},
                   {1,1,1,1,1,1,1,1,1},
                   {1,1,1,1,1,1,1,1,1},
                   {1,1,1,1,1,1,1,1,1},
                   {1,1,1,1,1,1,1,1,1},
                   {1,1,1,1,1,1,1,1,1},
                   {1,1,1,1,1,1,1,1,1},
                   {0,0,0,0,0,0,0,0,0}};

int bloquesaux[8][9]={{1,1,1,1,1,1,1,1,1},
                   {1,1,1,1,1,1,1,1,1},
                   {1,1,1,1,1,1,1,1,1},
                   {1,1,1,1,1,1,1,1,1},
                   {1,1,1,1,1,1,1,1,1},
                   {1,1,1,1,1,1,1,1,1},
                   {1,1,1,1,1,1,1,1,1},
                   {0,0,0,0,0,0,0,0,0}};
int vidas=3;


// x, y son las coordenadas de player. ex, ey las del enemigo
bool Collision(float x, float y, float ex, float ey,int width, int height){


    if(x+width < ex || x > ex+width || y+height < ey || y > ey+height){
        return false;
    }
    return true;
}
//funcion que detecta si el personaje principal esta sobre una plataforma
bool detectar_plataformas(int jx,int jy){
    for (int piso=0;piso<=8;piso++){  //for generado para los pisos del juego
        for (int posbloque=0;posbloque<=9;posbloque++){ //for generado para cada bloque en x
            int bloquex=125+(63*piso);
            int bloquey=(415-(150*posbloque))-distancia_max;
            if (((jx+32<125 && jx+32>0) || (jx+32<800 && jx+32>688)) && ((jy+85)>=bloquey) && ((jy+85)<=bloquey+13)){  //en esta condicion determina si el personaje esta en la zona donde no hay bloques
                return true;
            }
            if (bloques[posbloque][piso]==1){  //si hay un bloque en las coordenadas asignadas
                if ((jx+32>=bloquex && jx+32<=(bloquex+64)) && ((jy+85)>=bloquey) && ((jy+85)<=bloquey+13)){  //busca que las coordenadas de popo coincidan con las del bloque encontrado
                    return true;
                }
            }
        }
    }
    return false;
}
//funcion que determina si hay un bloque faltante en el camino de una foca
bool detectar_hueco(int jx,int jy){
    for (int piso=0;piso<=8;piso++){
        for (int posbloque=0;posbloque<=9;posbloque++){
            if (bloques[posbloque][piso]==0){
                int bloquex=125+(63*piso);
                if (((jx+32)>=bloquex && jx+32<=(bloquex+64)) && (jy==posbloque)){
                    bloques[posbloque][piso]=1;
                    return true;
                }
            }
        }
    }
    return false;
}

int detectar_bloque(int jx,int jy){
    for (int piso=0;piso<=8;piso++){
        for (int posbloque=0;posbloque<=9;posbloque++){
            int bloquex=125+(63*piso);
            int bloquey=(415-(150*posbloque))-distancia_max;
            if (((jx+32<125 && jx+32>0) || (jx+32<800 && jx+32>688)) && ((jy)>=bloquey) && ((jy)<=bloquey+20)){
                return 999;
            }
            if (bloques[posbloque][piso]==1){
                if ((jx+32>=bloquex && jx+32<=(bloquex+64)) && ((jy)>=bloquey) && ((jy)<=bloquey+15)){
                    return (posbloque*10)+piso;
                }
            }
        }
    }
    return 99;
}
int main() {

    int playerWidtth=0;
    int playerHeight=0;
    const float FPS=60.0; //fotogramas por segundos
    const float frameFPS=60.0;
    enum Direction {SALTO,ATAQUE,LEFT,RIGHT,};
    //posiciones horizontal y vertical
    float x=10,y=450;
    //velocidad del movimiento
    float moveSpeed=3;
    float velX, velY;
    velX=velY=0;
    int direction=SALTO, sourceX=64,sourceY=0;
    bool draw=true, active=false;
    //variable para salir del loop
    bool done=false;
    const float gravity=1;
    bool jump=false;
    bool ataq=false;
    float jumpSpeed=18;
    int velocidad_enemigos=1;



    //  Inicia allegro5, esto es necesario para realizar cualquier función de allegro
    //  Verifica si la función devuelve 0, si es asi, generará un mensaje de
    //  error, y el programa retornará -1 lo cual denota un programa fallido
    if(!al_init())
    {
        al_show_native_message_box(NULL,NULL,NULL,"failed to init allegro!",NULL,0);
        return -1;
    }


    //esta funcion permite usar el teclado
    al_install_keyboard();

    //permite cargar imagenes
    al_init_image_addon();

    // Crea un puntero a un DISPLAY y un BITMAP
    ALLEGRO_DISPLAY* frame=NULL;
    ALLEGRO_DISPLAY* foca=NULL;
    ALLEGRO_BITMAP *player=NULL;
    ALLEGRO_BITMAP *player2=NULL;
    ALLEGRO_BITMAP  *background=NULL;
    ALLEGRO_BITMAP *bloque2=NULL;


    //se declara un color
    ALLEGRO_COLOR electBlue=al_map_rgb(66,66,255);
    ALLEGRO_COLOR electGreen=al_map_rgb(66,255,66);

    //con esto se obtinene cual tecla es precionada en ese instante
    ALLEGRO_KEYBOARD_STATE keyState;

    //actualiza la ventana cada 0.01666 milisegundos
    ALLEGRO_TIMER *timer=al_create_timer(1.0/FPS);
    ALLEGRO_TIMER *frameTimer=al_create_timer(1.0/frameFPS);

    //cola de eventos
    ALLEGRO_EVENT_QUEUE *event_queue=al_create_event_queue();

    //  al_create_display(X,Y) y crea un ALLEGRO_DISPLAY de las dimensiones especificadas
    frame = al_create_display(ScreenWidth,ScreenHeight);

    if(!frame) //si no se puede crear la ventana, muestra un error
    {
        al_show_native_message_box(NULL,NULL,NULL,"failed to init frame!",NULL,0);
        return -1;
    }

    //Posicion de la ventana
    al_set_window_position(frame,200,100);

    //Funcion para redimensionar la pantalla
    al_set_new_display_flags(ALLEGRO_NOFRAME);
    //al_set_new_display_flags(ALLEGRO_OPENGL);

    if(!al_init_image_addon()) {
        al_show_native_message_box(frame, "Error", "Error", "Failed to initialize al_init_image_addon!",NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return 0;
    }
    /// se cargan las imagenes
    player = al_load_bitmap("spopo3.png");
    foca=al_load_bitmap("foca.png");
    player2= al_load_bitmap("spopo.png");
    background=al_load_bitmap("fondo.png");
    bloque2=al_load_bitmap("image10.png");
    playerWidtth=al_get_bitmap_width(player);
    playerHeight=al_get_bitmap_height(player);



    //registra la fuente del evento, recibe una cola de eventos y el tipo de evento
    al_register_event_source(event_queue,al_get_keyboard_event_source());
    al_register_event_source(event_queue,al_get_timer_event_source(timer));
    al_register_event_source(event_queue,al_get_timer_event_source(frameTimer));
    al_register_event_source(event_queue,al_get_display_event_source(frame));
    //al_register_event_source(event_queue,al_get_mouse_event_source());

    //al_hide_mouse_cursor(frame); //muestra el cursor

    al_start_timer(timer);
    al_start_timer(frameTimer);

    //loop principal del juego
    while(!done) {
        //instancia un nuevo evento
        ALLEGRO_EVENT events;
        //funcion que esta a la escucha de algun evento
        al_wait_for_event(event_queue,&events);
        al_get_keyboard_state(&keyState);

        if(events.type==ALLEGRO_EVENT_KEY_UP) {  // revisa si la tecla arriba es oprimida
            switch (events.keyboard.keycode) {
                case ALLEGRO_KEY_ESCAPE:
                    done=true;
                    break;
            }
        }
        else if(events.type==ALLEGRO_EVENT_TIMER){

            //Funcion que determina si la tecla derecha es oprimida
            if(events.timer.source==timer){
                active=true;
                if(al_key_down(&keyState,ALLEGRO_KEY_RIGHT)){
                    velX=moveSpeed;
                    direction = RIGHT;
                }
                else if(al_key_down(&keyState,ALLEGRO_KEY_LEFT)){					//Funcion que determina si la tecla izquierda es oprimida

                    velX=-moveSpeed;
                    direction = LEFT;
                }
                else if(al_key_down(&keyState,ALLEGRO_KEY_Z)){					//Funcion que determina si la tecla z es oprimida

                    ataq=true;
                    direction=ATAQUE;
                }else{
                    velX=0;
                    active=false;
                    if(al_key_down(&keyState,ALLEGRO_KEY_UP) && jump){					//Funcion que determina si la tecla arriba es oprimida

                        velY=-jumpSpeed;
                        jump=false;
                    }
                }
                //aqui se detectan las colisiones con los enemigos------------------------------------------------------------------------------

                for (int cont_foca=0;cont_foca<=11;cont_foca++){
                    if(Collision(x,y,focas[cont_foca][0],focas[cont_foca][1],68,47)) {  //funcion que detecta si una foca golpea a un jugador
                        printf("el jugador pierde una vida");
                        vidas-=1;
                        x=300;
                        y=200;
                    }
                }

            }

            else if(events.timer.source==frameTimer){
                if (active && ataq){
                    sourceX=sourceX-2;  //condicion que cambia el sprite si el ataque esta activado
                }
                if(active)
                    sourceX+=al_get_bitmap_width(player)/3;
                else
                    sourceX=72; //la imagen tiene 3 imagenes horizontalmente, cada un de 32 pixel en el eje X

                if(sourceX>=al_get_bitmap_width(player))
                    sourceX=0;
                sourceY=direction;
            }


            if(!jump)
                velY+=gravity; //al saltar, la velocidad sera hacia abajo en la pantalla aumentando en Y
            else
                velY=0;
            x+=velX;
            y+=velY;

            //GESTION DE MOVIMIENTO DE LOS ENEMIGOS----------------------------------------------------------------------------------------------------------------------

            for(int hielos=0;hielos<=11;hielos++){


            }

            for(int cont_focas=0;cont_focas<=11;cont_focas++){  //for que permite el movimiento de las focas
                if (focas[cont_focas][0]!=-99 && focas[cont_focas][1]!=-99){  // valida si existe una foca en la lista
                    float focax=focas[cont_focas][0];
                    float focay=focas[cont_focas][1];
                    bool devolverse=detectar_hueco(focax,focay);
                    if(focas[cont_focas][0]>750 || focas[cont_focas][0]<0){  //revisa si la foca paso los limites de la pantalla
                        if(focas[cont_focas][2]==0){
                            focas[cont_focas][2]=1;  //cambia la direccion si encuent
                        }
                        else{
                            focas[cont_focas][2]=0;
                        }
                    }
                    if (devolverse){
                        if(focas[cont_focas][2]==0){  //si la accion de devolverse esta activada
                            focas[cont_focas][2]=1;  // cambia la direccion
                        }
                        else{
                            focas[cont_focas][2]=0;  // cambia la direccion
                        }

                    }
                    if(focas[cont_focas][2]==0){   // revisa la rireccion de la foca
                        focas[cont_focas][0]-=velocidad_enemigos;  // mueve la foca en la direccion asignada
                    }
                    else{
                        focas[cont_focas][0]+=velocidad_enemigos;  //  mueve la foca
                    }

                }
            }

            //jump=detectar_plataformas(x,y); // linea que identifica las plataformas del juego--------------------------------------------------------------------------
            jump=detectar_plataformas(x,y);
            int bloque_golepado=detectar_bloque(x,y); // envia a revisar si hay un bloque golpeado
            int px=bloque_golepado/10;
            int py=bloque_golepado%10;
            if ((bloque_golepado!=99 && !jump) && velY<=0){  // revisa si hay algun bloque golpeado
                bloques[px][py]=0;                             // elimina el bloque que fue golpeado
                velY+=5;
            }
            if ((bloque_golepado==999 && !jump) && velY<=0){ // revisa si golpeo una zona protegida
                velY+=5;
            }
            if (y+85>=560){     // validacion que revisa si el personaje esta en la base principal
                if (distancia_max==0){  //si esta en la base
                    jump=true;
                }else{      //si no esta en la base principal
                    vidas-=1;
                    x=300;     // reinicia el personaje en x
                    y=200;     // reinicia el personaje en y
                }
            }
            if (y<=0){      // si la distancia del personaje es
                distancia_max-=5;
                y+=5;

            }

            //else  {jump=false;}
            if(distancia_max<=-719){
                printf("SIGUIENTE NIVEL");
                for (int piso=0;piso<=8;piso++){
                    for (int posbloque=0;posbloque<=9;posbloque++){
                        bloques[posbloque][piso]=1;
                    }
                }

                distancia_max=0;
                x=300;
                y=200;
                velocidad_enemigos+=4;
            }
            draw=true;
        }

        if(draw){
            al_draw_bitmap(background,0,-600-distancia_max,0); // se dibuja la imagen de fondo
            for (int piso=0;piso<=8;piso++){
                for (int posbloque=0;posbloque<=9;posbloque++){
                    if (bloques[posbloque][piso]==1){
                        al_draw_bitmap(bloque2,125+(63*piso),(415-(150*posbloque))-distancia_max,0);
                    }
                }
            }
            for (int cont_foca=0;cont_foca<=11;cont_foca++){
                int num=focas[cont_foca][2];
                if (num==-99){
                    num=1;
                }
                if (focas[cont_foca][0]!=-99 && focas[cont_foca][1]!=-99){
                    al_draw_bitmap_region(foca,num*68,0,68,47,focas[cont_foca][0],(415-(150*focas[cont_foca][1]))-47-distancia_max,NULL);
                }
            }
            al_draw_bitmap_region(player,sourceX,sourceY*al_get_bitmap_height(player)/4,64,85,x,y,NULL);

            al_draw_bitmap_region(player2,0,0,64,85,200,527,NULL);
            //pone la imagen en la ventana en la posicion (x,y)
            //al_draw_bitmap(player,x,y,0);

            //  Intercambia los buffers, ahora la ventana mostrará fond de color
            al_flip_display();

            //en este punto es donde se muestra el contenido e inmediatamente coloca el color de la ventana
            //para mostrar un nuevo cambio si que se vea el anterior


            //  La función limpia el buffer, con un color determinado, recibe como parámetro un ALLEGRO_COLOR.
            al_clear_to_color(al_map_rgb(0,0,0));
        }

    }
    //elimina la cola de eventos
    al_destroy_event_queue(event_queue);

    //elimina el bitmap
    al_destroy_bitmap(player);
    al_destroy_bitmap(foca);
    //elimina el timer
    al_destroy_timer(timer);
    //elimina el contenido bajo el puntero de ventana, esto eliminará a la ventana de la memoria.
    al_destroy_display(frame);

    return 0;
}


