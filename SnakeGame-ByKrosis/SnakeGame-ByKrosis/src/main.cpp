#include<SFML\Graphics.hpp>
#include<iostream>
/*
'##:::'##:'########:::'#######:: : '######::'####::'######:::::'########::'########::'########::'######::'######## : '##::: ##:'########::::'###:::::'##:::: :
##::'##:: ##.... ##:'##.... ##:'##... ##:. ##::'##... ##:::: ##.... ##: ##.... ##: ##.....::'##... ##: ##.....:: ###:: ##:... ##..::::'## ##:::'####::::
##:'##::: ##:::: ##: ##:::: ##: ##:::..::: ##:: ##:::..::::: ##:::: ##: ##:::: ##: ##::::::: ##:::..:: ##::::::: ####: ##:::: ##:::::'##:. ##::. ##:::::
#####:::: ########:: ##:::: ##:. ######::: ##::. ######::::: ########:: ########:: ######:::. ######:: ######::: ## ## ##:::: ##::::'##:::. ##::..::::::
##. ##::: ##.. ##::: ##:::: ##::..... ##:: ##:::..... ##:::: ##.....::: ##.. ##::: ##...:::::..... ##: ##...:::: ##. ####:::: ##:::: #########::'##:::::
##:. ##:: ##::. ##:: ##:::: ##:'##::: ##:: ##::'##::: ##:::: ##:::::::: ##::. ##:: ##:::::::'##::: ##: ##::::::: ##:. ###:::: ##:::: ##.... ##:'####::::
##::. ##: ##:::. ##:. #######::. ######::'####:. ######::::: ##:::::::: ##:::. ##: ########:. ######:: ########: ##::. ##:::: ##:::: ##:::: ##:. ##:::::
	..::::..::..:::: : ..:: : .......::::......:: : ....:: : ......::::::..:::::::: : ..:::: : ..::........:: : ......:: : ........::..::::..:::: : ..:::: : ..:::: : ..:: : ..::::::*/
//---------------------------PENDIENTES--------------------//
//1. Bloquear la tecla inversa a la dir del snake
//2. Arreglar Bug de Colision con ella misma desde el primer momento
#define LOG(x) std::cout<<x<<std::endl

//-----------------------------------------CONSTANTES DEL TABLERO---------------------------//
const int FILAS = 30, COLUMNAS = 20;							//Dimensiones del tablero
const int CUBOSIZE = 16;										//tamano en px de las imagenes
const int ANCHO = FILAS * CUBOSIZE;								//recorrer el tablero (ancho)
const int LARGO = COLUMNAS * CUBOSIZE;							//recorrer el tablero (largo)

//--------------------------------------ESTRUCTURA DE LA FRUTA---------------------------------//
struct Fruta
{
	int x, y;
} fruta;														//Contendra coordenadas de la comida


//----------------------------------------ESTRUCTURA DE SNAKE--------------------------------//
struct Snake
{
	int x, y;													//coordenadas de snake
} serpiente[100];												//objeto q almacenara hasta 100 cubos

int dir = 4;													//movimientos de serpiente (x,y)
int partes = 4;													//Cantidad de partes de serpiente al empezar
int puntaje = 0;												//puntos al tocar la fruta
bool movX = false;
bool movY = false;

void Crecimiento()
{
	//----------------------------------SEGUIMIENTO A LA CABEZA----------------------------//
		for (int i = partes; i > 0; i--)							//Hace que las partes de la snake sigan a la cabeza
		{															//La parte 'i' de snake obtiene las coordenadas de la parte 'i-1'
			serpiente[i].x = serpiente[i - 1].x;					//Le asigna a la ultima parte 'i' la coordenada X de parte 'i-1'
			serpiente[i].y = serpiente[i - 1].y;					//Lo mismo en la coordenada Y
		}
	

	//----------------------ASIGNAR DIRECCIONES AL MOVIMIENTO-------------------------//
																//Asignar cambios en direccion a cabeza
		if (dir == 0) { serpiente[0].y += 1;  } //abajo
		if (dir == 1) { serpiente[0].y -= 1;  }//arriba
		if (dir == 2) { serpiente[0].x += 1;  }//derecha
		if (dir == 3) { serpiente[0].x -= 1;  }//izq

	//-----------------------------COLISION CON FRUTA-------------------------------//
	if (serpiente[0].x == fruta.x && serpiente[0].y == fruta.y )
	{
		partes++;												//Aumenta la serpiente en 1 cubo
		puntaje += 10;											//le damos puntos

																//Generar nuevas coordenadas x,y
		fruta.x = rand() % FILAS;								//Genera un numero del 0 al 30
		fruta.y = rand() % COLUMNAS;							//Genera un numero del 0 al 20
		LOG(puntaje);
	}
}


void Colisiones()
{
	//--------------------------COLISION CON BORDES DEL TABLERO-------------------------//
	if (serpiente[0].x >= FILAS) serpiente[0].x = 0;				//la mueve al borde izquierdo
	if (serpiente[0].y >= COLUMNAS) serpiente[0].y = 0;			//la mueve al borde de arriba
	if (serpiente[0].x < 0) serpiente[0].x = FILAS;				//la mueve a la izquierda
	if (serpiente[0].y < 0) serpiente[0].y = COLUMNAS;			//la mueve a la derecha


	//--------------------------COLISION CON ELLA MISMA---------------------------------//
	
	
		for (int i = 0; i < partes; i++)							//activar el GAME OVER
		{
			if (serpiente[0].x == serpiente[i].x && serpiente[0].y == serpiente[i].y)
			{
				
			}
		}
}

int main()
{
	//----------------------------------VARIABLES TIEMPO DEL JUEGO------------------------//	
	sf::Clock clock;
	float temporizador = 0;										//almacenara el tiempo desde iniciar la ventana
	float delay = 0.1f;											//velocidad a la que va el juego
	
	//----------------------------------------CREAR VENTANA---------------------------------//
	sf::RenderWindow ventana( sf::VideoMode( ANCHO, LARGO ), "Snake Game/ByKrosis",sf::Style::Default );

	ventana.setFramerateLimit(60);								//Limita los FPS a 60(opcional)
	
	//----------------------------------------RECURSOS--------------------------------------//
	sf::Texture blanco, verde, rojo;							//Recuperar texturas de colores
	blanco.loadFromFile("imagenes/white.png");
	verde.loadFromFile("imagenes/green.png");			
	rojo.loadFromFile("imagenes/red.png");

	sf::Sprite pared(blanco), snake(verde), comida(rojo);		//Asignar texturas como sprites
	
																//Coordenadas iniciales para la fruta
	fruta.x = 10;
	fruta.y = 10;
	//---------------------------------------LOOP PRINCIPAL---------------------------------//
	while ( ventana.isOpen() )
	{
	//-------------------------------------MANAGER DEL TIEMPO-----------------------------//
		float time = clock.getElapsedTime().asSeconds();		//devuelve el tiempo al empezar en seg
		clock.restart();										//reinicia el tiempo a cero
		temporizador += time;									//Asigna el tiempo al temporizador							

	//------------------------------------MANAGER DE EVENTOS--------------------------------//
		sf::Event evt;											//var de acceso a eventos

		while ( ventana.pollEvent(evt) )						//sera TRUE si hay eventos pendientes
		{
			switch (evt.type)									//controla los eventos
			{
			 case sf::Event::Closed:							//cierra la ventana
				ventana.close();								
				break;
			 case sf::Event::Resized:							//imprime el tamano de la ventana(anchura,altura)
				 LOG(evt.size.width);
				 LOG(evt.size.height);
				break;		 
			 case sf::Event::KeyPressed:						//Salir al presionar ESC
				 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) ventana.close();
				break;
			}
		}

	//--------------------------------------DIRECCIONES DE MOVIMIENTO-----------------------------//
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) dir = 0; 
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) dir = 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) dir = 2; 
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  dir = 3;  

		if (temporizador > delay) { temporizador = 0; Crecimiento(); Colisiones(); }	//Inicia a la serpiente

		ventana.clear();						//Limpia la ventana a cada frame
		
	//-----------------------------------DIBUJAR OBJETOS EN PANTALLA------------------------//
		//------------------DIBUJAR TABLERO----------------------//
		for (int i = 0; i < FILAS; i++)							//DIBUJA el FONDO del tablero
		{
			for (int j = 0; j < COLUMNAS; j++)
			{													//recorre el tablero cada 16px
				pared.setPosition( (float) i * CUBOSIZE, (float) j * CUBOSIZE);		
				ventana.draw(pared);							//lo dibuja en ventana
			}
		}
		//------------------------DIBUJAR COMIDA------------------//
																//asigna coordenadas a comida en el tablero
		comida.setPosition( (float)fruta.x * CUBOSIZE , (float)fruta.y * CUBOSIZE );
		ventana.draw(comida);									//DIBUJA la COMIDA en pantalla

		//-----------------------DIBUJAR SERPIENTE----------------//
		for (int i = 0; i < partes; i++)						//DIBUJA SNAKE cubo x cubo
		{														//dibuja la cabeza en 0,0 al empezar
			snake.setPosition( (float)serpiente[i].x * CUBOSIZE , (float)serpiente[i].y * CUBOSIZE );
			ventana.draw(snake);								//lo muestra por pantalla
		}
		
	//-----------------------------------MUESTRA CAMBIOS DE VENTANA----------------------//
		ventana.display();										//muestra los cambios al siguiente frame
	}//while ( ventana.isOpen() )

	return 0;
}

