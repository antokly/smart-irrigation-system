#include "SendHTTPWebServer.h"

//variable to store the HTTP Request
String http_request_header = "";
int last_time = 0;

void http_send_data_to_web_page(String data)
{
  int time_to_wait = 5000;
    // Listener for incoming clients
  WiFiClient client = server.available();
  
  if(client){ //if a new client connects (On listener)

    //Time
    int current_time = millis();
    Serial.println("New Client");
    String current_line = ""; // make a String to hold incoming data from the client

    while(client.connected() && current_time - last_time <= time_to_wait){ // Loop tant que le client est connecté, et que c'est time to read
      //Setup le listener de http request header sur le client
      if(client.available()){

        char c = client.read(); //Cette ligne lit un octet (caractère) de données à partir du client 
                                //et le stocke dans la variable c.
        Serial.write(c);
        http_request_header += c;

        if(c == '\n'){  //Cette condition vérifie si le caractère lu est un saut de ligne (\n). 
                        //Cela indique la fin d'une ligne dans la requête HTTP envoyée par le client.
          if(current_line.length() == 0){
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // Display the HTML web page
            client.println("<!DOCTYPE html>");
            client.println("<html lang=\"en\">");
            client.println("<head>");
            client.println("<meta charset=\"UTF-8\">");
            client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
            client.println("<title>Humidity Data</title>");
            client.println("<style>");
            client.println(".encadre {");
            client.println("border: 4px solid #000;"); // Augmentez l'épaisseur de la bordure pour grossir le cadre
            client.println("padding: 20px;"); // Ajustez le padding pour décaler le contenu de l'encadrement
            client.println("width: 400px;"); // Augmentez la largeur de l'encadrement si nécessaire
            client.println("width: 400px;"); // Augmentez la largeur de l'encadrement si nécessaire
            client.println("width: 300px;"); // Ajustez la largeur de l'encadrement si nécessaire
            client.println("margin: 50px auto;"); // Ajustez la marge pour décaler l'encadrement par rapport au haut et au bas de la page
            client.println("text-align: center;");
            client.println("}");
            client.println("</style>");
            client.println("</head>");
            client.println("<body>");
            client.println("<div class=\"encadre\">");
            client.print("<p>Humidity: <span id=\"humidityValue\">");
            client.print(data);
            client.println("</span></p>");
            client.println("</div>");
            client.println("</body>");
            client.println("<script>");
            client.println("var humidity = document.getElementById(\"humidityValue\").textContent;");
            client.println("</script>");
            client.println("</html>");

            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          }else { // if you got a newline, then clear currentLine
            current_line = "";
          }
        }else if(c != '\r'){
          current_line += c;
        }
      }else{
        Serial.print("Client not available !\n");
      }
    }

    // Clear the header variable
    http_request_header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
    int last_time = current_time;
  }
}