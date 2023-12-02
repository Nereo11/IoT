#ifndef JSON_h
#define JSON_h
#include "Menu.h"
//Menu myData;
#include "ArduinoJson.h"

class json_factory{
public: 
String final_json = ";";

public: 
String make_json(void );
};

String json_factory :: make_json(void){
  String temporal = "";
 DynamicJsonDocument JSON ( 1024 );
JSON ["ID_Casilla"]=123;
JSON ["Latitud"]=197.23;
JSON ["Longitud"]=812121;
JSON ["Altitud"]=532;

JSON["CandidatoP"]= myMenu.nombreCandidatoPresidencia;
JSON["PartidoP"]= myMenu.nombrePartidoP;
JSON["CandidaturaP"]= myMenu.tipoCandidaturaP;

JSON["CandidatoG"]= myMenu.nombreCandidatoGobernatura;
JSON["PartidoG"]= myMenu.nombrePartidoG;
JSON["CandidaturaG"]= myMenu.tipoCandidaturaG;

JSON["CandidatoM"]= myMenu.nombreCandidatoMunicipal;
JSON["PartidoM"]= myMenu.nombrePartidoM;
JSON["CandidaturaM"]= myMenu.tipoCandidaturaM;



myrtc.get_time();
myrtc.format_date('/');
myrtc.format_time();
JSON["Fecha"]=  myrtc.fecha;
JSON["Hora"]= myrtc.tiempo;

serializeJsonPretty(JSON, temporal);
return temporal;
}
#endif