package ICE_Server;
import ICE_Logic.Enemy;
import ICE_Logic.Player;
import org.json.simple.parser.ParseException;
import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.lang.Integer;
import java.lang.Boolean;

public class Server {
    //Atributos de la clase Server
    private Socket socket;
    private Integer port = 9090; //Puerto en el que va a conectar
    private ServerSocket serverSocket;
    private Boolean running = true;

//------------Getters y Setters---------------//
    public Server(Player player) {
    }

    public Integer getPort() {

        return this.port;
    }

    public void setPort(Integer port) {
        this.port = port;
    }

    public Socket getSocket()
    {
        return socket;
    }

    public void setSocket(Socket socket) {
        this.socket = socket;
    }

    public ServerSocket getServerSocket() {
        return serverSocket;
    }

    public void setServerSocket(ServerSocket serverSocket) {
        this.serverSocket = serverSocket;
    }

    public boolean isRunning() {
        return running;
    }

    public void setRunning(Boolean running) {
        this.running = running;
    }

    public void start(Player player) throws IOException, ParseException {
        this.local(player);
        System.out.println("Server Irreconozible");
    }


    private void local(Player player) throws IOException, ParseException {
            this.serverSocket = new ServerSocket(port);
            System.out.print("ICE_Server is listening in port: " + port + "\n");


            while (true) {
                //Empieza a conectar requests del cliente
                Socket socket = serverSocket.accept();
                System.out.print("New client connected\n");
                //Leer data del array del cliente (read to byte array)
                InputStream input = socket.getInputStream();
                BufferedReader reader = new BufferedReader(new InputStreamReader(input), 1024);

                //Escribe data en el array
                OutputStream output = socket.getOutputStream();
                //Convierte byte array a Texto
                PrintWriter writer = new PrintWriter(output, true);


                char inputData[] = new char[1024];//Buffer (Char array)

                //Lee el cliente mientras actualiza los objetos
                do {

                    reader.read(inputData, 0, 1024);
                    System.out.println(String.valueOf(inputData).trim());
                    player.update(String.valueOf(inputData).trim());
                    writer.println(player.PlayerToJson());
                    this.running = false;

                } while (running);

                //Close socket connection
                socket.close();

            }

    }

    public static  void  main(String[] args) throws IOException, ParseException {
    Player popo = new Player(50,100,0,3);
    popo.PlayerToJson();
    Player popo2 = new Player(70,180,1,2);
    popo.update(popo2.PlayerToJson().toJSONString());
    Enemy foca = new Enemy(52,250,1);
    foca.createEnemyJson();
    Server server=new Server(popo);
    server.start(popo);
    }
}

