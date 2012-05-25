#include "stdafx.h"
#include "Memory.h"
#include <string>
#include <stdlib.h>
#include <iostream>
#include <fstream>

#include <conio.h>

	
using std::string;
using std::getline;

using namespace std;

class MIPS
{
public:
	
	Memory Memoria;// Objeto para acessar os métodos da memória
		
	///////////// DEFINIÇÃO DOS MÈTODOS///////////
void load()
	{
        unsigned long int instruction;
		int cont=1;
		char end[400],palavra[33];//Aqui é a palavra que está no arquivo;
	    PC=1;
		ciclos=0;// PC foi definido aqui, por que se fosse definido em Fetch, a cada ciclo ele voltaria para 1.
		ifstream leitura; //objeto de leitura de arquivo.
		
		cout<<"Entre com o endereco onde esta localizado o arquivo que sera lido.\nExemplo:\"C:/exemplo/teste.txt\""<<endl;
		cin>>end;
		
        leitura.open(end); // abertura de arquivo.
        if(!leitura.is_open( ))  // Saber se o arquivo foi aberto.
        {
		  system("cls");
          cout<<"\t\t\tERRO!! CODE:0x001";
          leitura.clear( ); //reseta o objeto leitura, para limpar memória do sistema
          _getch();
		  exit(0);
        }
	   
	    system("cls");
	    cout<<"\t\t\tArquivo aberto com sucesso!"<<endl;
		cout<<"\nPressione qualquer tecla para que seu codigo seja processado";
		_getch();
        while(leitura.getline(palavra,33))//lê o arquivo, os 32 bits até o \n e armazena em palavra, até o fim do arquivo
        {
             instruction=strtoul(palavra,NULL,2);//converte de string para unsigned long int.
             Memoria.write(cont,instruction);
			 cont+=4;
			 ciclos++;
	    }
		
       leitura.close();
      
	}
void fetch()
{
	unsigned long int instruction;
	instruction=Memoria.read(PC);
	itoa(instruction,IR,2);
	PC+4;
}
void complementar()
{
	int i,qtd;
	char comp_zeros[33];
	qtd=strlen(IR);

	for(i=0;i<=32;i++)
	{
	  comp_zeros[i]=NULL;
    }

	i=0;
	while(qtd<32)
	{
	   comp_zeros[i]='0';
	   qtd++;
	   i++;
	}

	strcat(comp_zeros,IR);
			  
	for(i=0;i<=32;i++)
	{
      IR[i]=comp_zeros[i];
    }
}
void decode()
{
	unsigned int qtd;
	qtd=strlen(IR);
	if(qtd<32)
	{
      complementar();
    }
	if(qtd>32)
	{
    		system("cls");
 			printf("ERRO CODE:0x004");
			_getch();
			exit(0);
	}
	string s;
    s=IR;
          

	enum opcodes
	{
      LW=35,
      SW=43,
	};

	enum funct
	{
      ADD=32,
      MUL=24,
      DIV=26,
      SUB=34,
	};
    unsigned int opcodeDEC;
	s.copy(opcode,6,0);
	opcode[6]=NULL;
	opcodeDEC=strtoul(opcode,NULL,2);

	if(opcodeDEC!=35 && opcodeDEC!=43 && opcodeDEC!=0)
	{
		system("cls");
		cout<<"ERRO CODE:0x005";
		_getch();
		exit(0);
	}

	unsigned int functDEC;
    s.copy(Funct,6,26);
	Funct[6]=NULL;
    functDEC=strtoul(Funct,NULL,2);
	if(functDEC != 32 && functDEC!=24 && functDEC!=26 && functDEC!=34)                                        
	{
		system("cls");
		cout<<"ERRO CODE:0x006";
		_getch();
		exit(0);
	}

	switch (opcodeDEC)
	{
	   case LW:
		    s.copy(rs,5,6);
			rs[5]=NULL;
		
			s.copy(rt,5,11);
			rt[5]=NULL;

			s.copy(rd,5,16);
			rd[5]=NULL;
			
			break;
	   case SW:
		    
		    s.copy(rs,5,6);
			rs[5]=NULL;
		
			s.copy(rt,5,11);
			rt[5]=NULL;

			s.copy(rd,5,16);
			rd[5]=NULL;


		    break;

	   case 0:
			   
		   if(functDEC==32)
		   {
				s.copy(rs,5,6);
				rs[5]=NULL;
				
				s.copy(rt,5,11);
				rt[5]=NULL;

				s.copy(rd,5,16);
				rd[5]=NULL;

				s.copy(sa,5,21);
				sa[5]=NULL;
		   }
		   if(functDEC==24)
		   {
			    s.copy(rs,5,6);
				rs[5]=NULL;
				
				s.copy(rt,5,11);
				rt[5]=NULL;

				s.copy(rd,5,16);
				rd[5]=NULL;

				s.copy(sa,5,21);
				sa[5]=NULL;
		   }
		   if(functDEC==26)
		   {
			    s.copy(rs,5,6);
				rs[5]=NULL;
				
				s.copy(rt,5,11);
				rt[5]=NULL;

				s.copy(rd,5,16);
				rd[5]=NULL;

				s.copy(sa,5,21);
				sa[5]=NULL;
		   }
		   if(functDEC==34)
		   {
			    s.copy(rs,5,6);
				rs[5]=NULL;
				
				s.copy(rt,5,11);
				rt[5]=NULL;

				s.copy(rd,5,16);
				rd[5]=NULL;

				s.copy(sa,5,21);
				sa[5]=NULL;
		   }
		   break;
		}
	}
}
void dump_regs()
{	
		int opc;
		system("cls");
		cout<<"\nRS= "<<rs;

		std::cout<<"\nOpcode= "<<opcode
		<<"\n$s0= "<<rs
		<<"\n$s1= "<<rt
		<<"\n$st= "<<rd
		<<"\nFunct= "<<Funct
		<<endl;

		cout<<"\nSelecione a opcao desejada:\n1-Ver resultado em decimal\n0-Sair do programa\n ";
		cin>>opc;
		if(opc==1)
		{
			unsigned int rsDEC,rtDEC,rdDEC,saDEC,functDEC,opcodeDEC;
			rsDEC=strtoul(rs,NULL,2);
			rtDEC=strtoul(rt,NULL,2);
			rdDEC=strtoul(rd,NULL,2);
			functDEC=strtoul(Funct,NULL,2);
			opcodeDEC=strtoul(opcode,NULL,2);

			cout<<"\nOpcode= "<<opcodeDEC
			<<"\n$s0= "<<rsDEC
			<<"\n$s1= "<<rtDEC
			<<"\n$st= "<<rdDEC
			<<"\nFunct= "<<functDEC
			<<endl;
			_getch();
			system("cls");
			cout<<"\t\tObrigado por usar o simulador de arquitetura Mips Basic\n\t\t    Developed by: Renato Fernandes e Ivan Lopes";
			_getch();
		}
		if(opc==0)
		{
			system("cls");
			cout<<"\t\tObrigado por usar o simulador de arquitetura Mips Basic\n\t\t    Developed by: Renato Fernandes e Ivan Lopes";
			_getch();
		}
}
void step()
{
	fetch();
	decode();
	execute();
}
void run()
	{	
		while(ciclos>0)	
		{
			step();
			ciclos--;
		}

	}

	//REGISTRADORES
	int HI;
	char opcode[7];
    char rd[25];
    char rs[6];
    char rt[6];
    char sa[6];
    char Funct[7];
	int ciclos;
	char IR[33];
    int PC;
};

int main()
{
	MIPS Obj;
	int opc;
	cout<<"\t\t\tBem Vindo ao Simulador de arquitetura MIPS\n\n";
	Obj.load();
	Obj.run();
	system("cls");
	cout<<"\t\t\t Operacao realizada com sucesso!!\n\nPressione a opcao desejada: ";
	cout<<"\n1-Para ver os registradores\n2-Para carregar um novo arquivo\n3-Para sair do programa\n";
	cin>>opc;
	if(opc==1)
	{
		Obj.dump_regs();
	}
	if(opc==2)
	{
		system("cls");
		main();
	}
	if(opc==3)
	{
		system("cls");
		cout<<"\t\tObrigado por usar o simulador de arquitetura Mips Basic\n\t\t    Developed by: Renato Fernandes e Ivan Lopes";
		_getch();
	}
	return 0;
}
