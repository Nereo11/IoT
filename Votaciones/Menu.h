#ifndef Menu_h
#define Menu_h

//#include <LiquidCrystal_I2C.h>
#define pinup 16
#define pindown 17
#define pinleft 34
#define pinright 35
#define pinaccept 32
#define buzzer 14

//initialize the library
//LiquidCrystal_I2C lcd(0x20,16,2);

class Menu {
  public:
    String nombrePartidoP;
    String nombrePartidoG;
    String nombrePartidoM;

    String tipoCandidaturaP;
    String tipoCandidaturaG;
    String tipoCandidaturaM;

    String nombreCandidatoPresidencia;
    String nombreCandidatoGobernatura;
    String nombreCandidatoMunicipal;

    bool nombresCompletos = false;

    String nombresTemp[3]; // Temporal para almacenar un candidato por cada tipo de candidatura
    int nombresGuardados = 0;


    int stateup = LOW,
        statedown = LOW,
        stateleft = LOW,
        stateright = LOW,
        stateaccept = LOW;
    int option = 0, category = 0;
    char* menu[3][4];
  public:
    void initMenu ( void );
    void menuActions ( void );
    void sound(int frequency); 
    void accept ( void );

  private:
  bool votoPresidencia = false;
  bool votoGobernatura = false;
  bool votoMunicipal = false;
};

void Menu :: initMenu ( void ) {
  //delcare the category and options for the menu
  menu[0][0] = "Presidencia";
  menu[1][0] = "Gobernatura";
  menu[2][0] = "Municipal";

  menu[0][1] = "PUP: Julieta Miramontes";
  menu[0][2] = "PFN: Maximiliano Ortiz";
  menu[0][3] = "PPC: Hiromi Mayoral";

  menu[1][1] = "PUP: Axel Mora";
  menu[1][2] = "PFN: Lina Diaz";
  menu[1][3] = "PPC: Victor Barboza ";

  menu[2][1] = "PUP: Federico Aguilar";
  menu[2][2] = "PFN: Teodoro Brambilia";
  menu[2][3] = "PPC: Gabriela Gallardo";


  //declare the pin mode
  //pinMode(buzzer, OUTPUT);
  pinMode(pinup, INPUT);
  pinMode(pindown, INPUT);
  pinMode(pinleft, INPUT);
  pinMode(pinright, INPUT);
  pinMode(pinaccept, INPUT);
  
  //initialize the lcd
  ACT.lcd_init();
  //turn on the backlight
  //lcd.backlight();
  //write "menu"
  lcd.setCursor(0,0);
  lcd.print("Menu ");
  //display the custom icons
  //byte customone[] = {B10001,B01110,B01110,B10101,B01110,B01110,B01010,B01010};
  //byte customtwo[] = {B10001,B01110,B01110,B10101,B00100,B00100,B10101,B01110};
  //byte customthree[] = {B00100,B01110,B00100,B01110,B10101,B11111,B01110,B00100};
byte customone[] = {
  B01110,
  B10001,
  B10001,
  B10101,
  B10001,
  B10001,
  B01010,
  B00100
};

byte customtwo[] = {
  B10101,
  B10101,
  B11111,
  B01110,
  B00100,
  B00100,
  B00100,
  B00100
};

byte customthree[8] = {
  B00100,
  B00100,
  B00100,
  B00100,
  B11111,
  B01110,
  B00100,
  B00100
};




  lcd.write(byte(0));
  lcd.write(byte(1));
  lcd.write(byte(2));
  lcd.createChar(0, customone);
  lcd.createChar(1, customtwo);
  lcd.createChar(2, customthree);
}

void Menu::sound(int frequency) {
  tone(buzzer, frequency);
  delay(100); // Ajusta este tiempo según lo que necesites para el sonido
  noTone(buzzer);
  delay(100);
}


void Menu :: menuActions ( void ) {
  //declare the state for buttons
  stateup = digitalRead(pinup);
  statedown = digitalRead(pindown);
  stateleft = digitalRead(pinleft);
  stateright = digitalRead(pinright);
  stateaccept = digitalRead(pinaccept);

  
  //right and left direction
  
  if(stateright == HIGH) {
    option = 1;
    sound(300);
  } else if (stateleft == HIGH) {
  	option = 0;
    sound(300);
  }

   

  //up and down direction for the options
  if(stateup == HIGH && option != 0 && option != 1) {
   	 option--;
     sound(900);
  	} else if (statedown == HIGH && option != 0 && option < 3) {
  	 option++;
     sound(900);
  	} 
    
    //up and down direction for the categories
    if(stateup == HIGH && option == 0 && category > 0) {
   	 category--;
     sound(900);
  	} else if (statedown == HIGH && option == 0 && category < 2) {
  	 category++;
     sound(900);
  	}



  ACT.imprimir(menu[category][option], 1);
      
if (stateaccept == HIGH) {
    sound(700);
    myrtc.get_time();
    myrtc.format_time();

    if (!nombresCompletos) {
        if (category == 0 && !votoPresidencia) {
            // Almacenar el voto para la Presidencia
            nombreCandidatoPresidencia = menu[category][option];
            nombreCandidatoPresidencia.remove(0, 5); // Eliminar el partido por posiciones
            tipoCandidaturaP = "Presidente";

            if (option == 1) {
                nombrePartidoP = "PUP";
            } else if (option == 2) {
                nombrePartidoP = "PFN";
            } else if (option == 3) {
                nombrePartidoP = "PPC";
            }

            votoPresidencia = true; // Marcar que se ha registrado un voto para la Presidencia
        } else if (category == 1 && !votoGobernatura) {
            // Almacenar el voto para la Gobernatura
            nombreCandidatoGobernatura = menu[category][option];
            nombreCandidatoGobernatura.remove(0, 5); // Eliminar el partido por posiciones
            tipoCandidaturaG = "Gobernador";

            if (option == 1) {
                nombrePartidoG = "PUP";
            } else if (option == 2) {
                nombrePartidoG = "PFN";
            } else if (option == 3) {
                nombrePartidoG = "PPC";
            }

            votoGobernatura = true; // Marcar que se ha registrado un voto para la Gobernatura
        } else if (category == 2 && !votoMunicipal) {
            // Almacenar el voto para la Municipal
            nombreCandidatoMunicipal = menu[category][option];
            nombreCandidatoMunicipal.remove(0, 5); // Eliminar el partido por posiciones
            tipoCandidaturaM = "Municipal";

            if (option == 1) {
                nombrePartidoM = "PUP";
            } else if (option == 2) {
                nombrePartidoM = "PFN";
            } else if (option == 3) {
                nombrePartidoM = "PPC";
            }

            votoMunicipal = true; // Marcar que se ha registrado un voto para la Municipal
        } else {
          if (votoPresidencia && votoGobernatura && votoMunicipal) {
            nombresCompletos = true; // Marcar que se han registrado los tres votos
           }
            // Ya se ha registrado un voto para esa categoría
            lcd.setCursor(0, 1);
            lcd.print("Ya votaste en esta categoria");
            delay(1000);
        }
    } else {
        // Si ya se han almacenado los tres nombres
        // Mostrar un mensaje en la pantalla
        lcd.setCursor(0, 1);
        lcd.print("Ya tienes 3 nombres");
        delay(1000);
    }
}
/*
      if(stateaccept == HIGH){   
      sound(700);       
      myrtc.get_time();
      myrtc.format_time();

if (nombresGuardados < 3 && !nombresCompletos) {
            // Almacena un candidato por cada tipo de candidatura
            nombresTemp[category] = menu[category][option];
            nombresTemp[category].remove(0, 5); // Elimina el partido por posiciones
            nombresGuardados++;

            // Si se han almacenado los tres nombres, asigna cada uno a las variables correspondientes
            if (nombresGuardados == 3) {
               nombresCompletos = true;
                for (int i = 0; i < 3; ++i) {
                    if (nombresTemp[i] != "") {
                        if (i == 0) {
                            nombreCandidatoPresidencia = nombresTemp[i];
                            tipoCandidaturaP = "Presidente";
                            if (option == 1) {
        nombrePartidoP = "PUP";
      } else if (option == 2) {
        nombrePartidoP = "PFN";
      } else if (option == 3) {
        nombrePartidoP = "PPC";
      }
                        } else if (i == 1) {
                            nombreCandidatoGobernatura = nombresTemp[i];
                            tipoCandidaturaG = "Gobernador";
                            if (option == 1) {
        nombrePartidoG = "PUP";
      } else if (option == 2) {
        nombrePartidoG = "PFN";
      } else if (option == 3) {
        nombrePartidoG = "PPC";
      }
                        } else if (i == 2) {
                            nombreCandidatoMunicipal = nombresTemp[i];
                            tipoCandidaturaM = "Municipal";
                            if (option == 1) {
        nombrePartidoM = "PUP";
      } else if (option == 2) {
        nombrePartidoM = "PFN";
      } else if (option == 3) {
        nombrePartidoM = "PPC";
      }
                        }
                    }
                }
            }
        } else {
            // Si ya se han almacenado los tres nombres
            // Muestra un mensaje en la pantalla
            lcd.setCursor(0, 1);
            lcd.print("Ya tienes 3 nombres");
            delay(1000);
        }
    }
*/



    /*

      if (category == 0) {
      tipoCandidatura = "Presidencia";

      nombreCandidato = menu[category][option];
      nombreCandidato.remove(0,5);
      //Esto cambiaria si se logra añadir una tercer categoria
            if (option == 1) {
        nombrePartido = "PUP";
      } else if (option == 2) {
        nombrePartido = "PFN";
      } else if (option == 3) {
        nombrePartido = "PPC";
      }


    } else if (category == 1) {
      tipoCandidatura = "Gobernatura";
      nombreCandidato = menu[category][option];
      nombreCandidato.remove(0,5);
      //Esto cambiaria si se logra añadir una tercer categoria
            if (option == 1) {
        nombrePartido = "PUP";
      } else if (option == 2) {
        nombrePartido = "PFN";
      } else if (option == 3) {
        nombrePartido = "PPC";
      }


    } else if (category == 2) {
      tipoCandidatura = "Municipal";
      nombreCandidato = menu[category][option];
      nombreCandidato.remove(0,5);
      //Esto cambiaria si se logra añadir una tercer categoria
            if (option == 1) {
        nombrePartido = "PUP";
      } else if (option == 2) {
        nombrePartido = "PFN";
      } else if (option == 3) {
        nombrePartido = "PPC";
      }
    }
  }*/
}


#endif