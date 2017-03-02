/* A Spark function to parse the commands */
int ledControl(String command);

// Asignacion de Pines
int aspersor1 = D5; 
int aspersor2 = D6;
int aspersor3 = D7;
//int aspersor4 = D4;       //RElay 4 no sera usado por el mometo

//Variables para monitorear la ultia vez que rego cada valvula.
int riego_ant_aspersor1;
int riego_ant_aspersor2;
int riego_ant_aspersor3;

//int riego_ant_aspersor4;

//Variables para controlar la ultima vez que se detubo el Riego [CANCELACION O CICLO COMPLETO]
int stop_aspersor1;
int stop_aspersor2;
int stop_aspersor3;
//int stop_aspersor4;

//Los SEGUNDOS necesarios para que una activacion cuente como NUEVO RIEGO..
int delay_riego = 5; //los 5 segundos son de prueba ...creo q deben ser 60 seg.

// This routine runs only once upon reset
void setup() 
{
    
  //Declaracion de Funciones que recibiran instucciones de a la NUBE <---- SMARTTHINGS
  Particle.function("sprinkler1", valvula1);    //"ledstate" debera ser cambiado por el irrigation
  Particle.function("sprinkler2", valvula2);
  Particle.function("sprinkler3", valvula3);
 // Particle.function("sprinkler4", valvula4);
    
    
  // declaracion de los PINES de Salida (Control VAlvulas) y el estado Inicial siempre sera apagadas.
  pinMode(aspersor1, OUTPUT);
  digitalWrite(aspersor1, LOW);
  pinMode(aspersor2, OUTPUT);
  digitalWrite(aspersor2,  LOW);
  pinMode(aspersor3, OUTPUT);
  digitalWrite(aspersor3, LOW);
  //pinMode(aspersor4, OUTPUT);
  //digitalWrite(aspersor4, LOW);
  
  //Variable que sera leida por SMARTTHINGS para identificar en que estado estan las Vavulas.
  Particle.variable("checkStatus1", "off");
  Particle.variable("checkStatus2", "off");
  Particle.variable("checkStatus3", "off");
  Particle.variable("checkStatus4", "off");
  
   Particle.variable("ult-valv1",0);
}

// This routine loops forever 
void loop()
{
  // Nothing to do here
}
/*
int valvula1(String command)
{
  if (command == "1") {   
    digitalWrite(aspersor1, HIGH);   // Enciende aspersor1
    return 1;
  } else {               
    digitalWrite(aspersor1, LOW);    // Apaga aspersor1
    return 0;
  }
}*/

int valvula1(String command)
{
  if (command == "1") {
      int now = Time.now();
            if (now - riego_ant_aspersor1 > delay_riego) {
                riego_ant_aspersor1 = now;          //Actulaiza el Inicializacion del ULTIMO riego
                 digitalWrite(aspersor1, HIGH);   // Enciende aspersor1
                 Particle.variable("checkStatus1", "on");
                  Particle.variable("ult-valv1", riego_ant_aspersor1);
            }
    return 1;
  } else {               
    digitalWrite(aspersor1, LOW);    // Apaga aspersor1
    stop_aspersor1 = Time.now();
    Particle.variable("checkStatus1", "off");
    return 0;
  }
}

int valvula2(String command)
{
  if (command == "1") {
      int now = Time.now();
            if (now - riego_ant_aspersor2 > delay_riego) {
                riego_ant_aspersor2 = now;          //Actulaiza el Inicializacion del ULTIMO riego
                 digitalWrite(aspersor2, HIGH);   // Enciende aspersor2
                 Particle.variable("checkStatus2", "on");
            }
    return 1;
  } else {               
    digitalWrite(aspersor1, LOW);    // Apaga aspersor2
    stop_aspersor2 = Time.now();
    Particle.variable("checkStatus2", "off");
    return 0;
  }
}

int valvula3(String command)
{
  if (command == "1") {
      int now = Time.now();
            if (now - riego_ant_aspersor3 > delay_riego) {
                riego_ant_aspersor3 = now;          //Actulaiza el Inicializacion del ULTIMO riego
                 digitalWrite(aspersor3, HIGH);   // Enciende aspersor3
                 Particle.variable("checkStatus3", "on");
            }
    return 1;
  } else {               
    digitalWrite(aspersor3, LOW);    // Apaga aspersor3
    stop_aspersor3 = Time.now();
    Particle.variable("checkStatus3", "off");
    return 0;
  }
}
