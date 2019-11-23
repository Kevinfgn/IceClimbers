package ICE_Logic;
import org.json.simple.JSONObject;
import java.lang.Integer;

public class Enemy {

    Integer posX;
    Integer posY;
    Integer direccion;

    public Enemy(Integer posX, Integer posY, Integer direccion) {
        this.posX = posX;
        this.posY = posY;
        this.direccion = direccion;
    }

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

    public Integer getDireccion() {
        return direccion;
    }

    public void setDireccion(Integer direccion) {
        this.direccion = direccion;
    }

    //Enemies
    public JSONObject createEnemyJson(){
        JSONObject json=new JSONObject();
        json.put("posX",this.getPosX());
        json.put("posY", this.getPosY());
        json.put("direccion",this.getDireccion());
        //System.out.println(json);
        return json;
    }


    public void destroyEnemy(){

    }



}
