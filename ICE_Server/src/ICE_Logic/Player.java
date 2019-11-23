package ICE_Logic;

import  org.json.simple.*;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;
import java.lang.Integer;



public class Player {

    //Atributos de la Clase Jugador
    private Integer posX;//Determines character X position
    private Integer posY;//Determines character y position
    private Integer attack;//Determines character score
    private Integer lives;//Determines character lives

    //Constructor

    public Player(Integer posX,Integer posY,Integer attack, Integer lives){
        this.posX=posX;
        this.posY=posY;
        this.attack=attack;
        this.lives=lives;
    }

    //********************** Setters and Getters ************************//

    public Integer getPosX() {
        return posX;
    }

    public void setPosX(Integer posX) {
        this.posX = posX;
    }

    public Integer getPosY() {
        return posY;
    }

    public void setPosY(Integer posY) {
        this.posY = posY;
    }

    public Integer getScore() {
        return attack;
    }

    public void setScore(Integer score) {
        this.attack = score;
    }

    public Integer getLives() {
        return lives;
    }

    public void setLives(Integer lives) {
        this.lives = lives;
    }



    public void update(String json) throws ParseException {
        JSONParser parser = new JSONParser();
        JSONObject  jsonNew = (JSONObject ) parser.parse(json);
        this.posX = (int) ((long) jsonNew.get("posX"));
        this.posY = (int) ((long)jsonNew.get("posY"));
        this.attack = (int) ((long)jsonNew.get("attack"));
        this.lives = (int) ((long)jsonNew.get("lives"));
        System.out.println(json);
    }

    //Returns character data as a json object to be sent to the client

    public JSONObject PlayerToJson(){
        JSONObject json=new JSONObject ();
        json.put("posX",this.posX);
        json.put("posY", this.posY);
        json.put("attack",this.attack);
        json.put("lives",this.lives);
        System.out.println(json);
        return json;
    }

}
