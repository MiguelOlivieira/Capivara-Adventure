// Bibliotecas
#include <stdio.h >	// Biblioteca de entrada e saida de dados
#include <string.h > //Biblioteca para usar o strcpy
#include <stdlib.h > //Pra usar o exit

// Defini��es
#define MAX_INVENTARIO 10 // Define o valor maximo do inventario

/*
 *
 *Nosso algoritimo simula um jogo de RPG medieval em que o jogador vai se aventurar pelas mais divertidas e inexperadas situa��es. 
 *Contendo alem de uma historia envolvente, uma experiencia intrigante com a descoberta da capivara magica.
 *
 *Contemos fun��es:
 *
 *## Para cada estado e cenario da historia.
 *## Inserir elemento
 *## Deletar elemento
 *## Buscar elemento
 *## Listar elemento
 *## Atualizar elemento
 * 
 *Alem das demais como por exemplo:
 *
 *## Menu inicial
 *## Menu de op��es
 *## Classes 
 *## Cen�rios no geral como loja e tarverna.
 *
 *ATEN��O: VERS�O DEMO DO JOGO!
 *AUTORES: Jos� Miguel & Renato Louren�o
 *
 */

// Fun��es Globais 
void removerPersonagem(); // Opera��o para remover personagem
void resumoPersonagem(char *nome, char *classe); // Opera��o de resumo inicial
void criarPersonagem(void);	// Atualiza a struct 
void classeEscolhida(int escolhaClasse, char *classe); // Atualiza a classe no struct
void jogoIniciado(char *nome); // Inicio da historia 
void explorarCidade(int resposta); // Cenario da cidade
void loja(); // Loja de itens
void entrarTaverna(void);	//Fun��o para op��o de entrar na Taverna
void anaoDialogo(void);	// Dialogo com NPC
void torreVelha(void); // Cenario/Evento
void entrarBuraco(void); // Cenario/Evento
void olharParaTras(void); // Cenario/Evento
void opcoes(); // Menu de op��es do usuario
void retornarJogo(); // Checkpoit para o jogador quando sair do menu retornar onde estava
void listarMochila(char inventario[][20], int tamanho);	// Itens na mochila
void inserirElemento(char inventario[][20], int *tamanho, const char *item); // Inserir itens na mochila

int tamanhoInventario = 3; // Tamanho Inicial do inventario 
int exibirTexto(char *descricao, char *escolhas[]);	// 
int exibirTextoOpcoes(char *descricao, char *escolhas[]); // Fun��o dedicada aos dialogos 
char inventario[MAX_INVENTARIO][20] = { "Bussola" };// Definindo os itens iniciais, junto com o array

// Estrustura do usuario 
typedef struct personagem
{
	char nome[20];
	int nivel;
	float exp;
	char classe[10];

}

Personagem;

// Evita looping em caso da informa��o inserida ser diferente do tipo da variel que vai receber a escolha 
void limparBuffer()
{
	char c;
	do {
		c = getchar();
	} while (c != '\n');
}

// Fun��o globais iniciadas ap�s a struct por depender das informa��es que l� constam
void buscarPersonagem(Personagem *personagemArray, int contagem); // Fun��o que busca e lista
void salvarDados(Personagem *personagemArray, int nivel); // Salva os dados no arquivo TXT 
int personagemExistente = 0; // Variavel global
int resposta = 0; // Variavel global
int checkPoint = 0; // Variavel global
Personagem nome; // Variavel global
Personagem * pntr;  // Ponteiro para a struct personagem
Personagem personagem1; // Modificando a struct

// Salva os dados em um arquivo TXT
void salvarDados(Personagem *personagemArray, int nivel)
{
	FILE *arquivo = fopen("arquivo.txt", "w");
	if (arquivo == NULL)
	{
		printf("Erro ao abrir o arquivo\n");
		return;
	}

	if (nivel == 0)
	{
		printf("Nenhum personagem cadastrado\n");
		fclose(arquivo);	// Fechar o arquivo antes de retornar
		return;
	}

	for (int i = 0; i < nivel; ++i)
	{
		fprintf(arquivo, "%s\n", personagemArray[i].nome);
		fprintf(arquivo, "%d\n", personagemArray[i].nivel);
		fprintf(arquivo, "%f\n", personagemArray[i].exp);
		fprintf(arquivo, "%s\n", personagemArray[i].classe);
	}

	fclose(arquivo);
}

// Le as informa��es do arquivo
void carregarDados(Personagem *personagemArray, int nivel)
{
	FILE *arquivo = fopen("arquivo.txt", "r");

	if (arquivo == NULL)
	{
		printf("Erro ao abrir o arquivo\n");
		return;
	}

	char nome[20];
	float exp;
	char classe[10];

	while (fscanf(arquivo, "%s", nome) == 1)
	{
		fscanf(arquivo, "%d", &nivel);
		fscanf(arquivo, "%f", &exp);
		fgetc(arquivo);
		fscanf(arquivo, "%s", &classe);
		// colocar uma fun��o para receber essas informa��es do FILE 
		fgetc(arquivo);
	}

	fclose(arquivo);

}

// Fun��o main que contem o menu inicial de op��es
int main()
{ 

	/*Menu inicial*/
	
	int escolha;
	printf("Bem vindo(a), aventureiro(a). Escolha uma das opcoes abaixo:\n\n");
	printf("1- Jogar\n");
	printf("2- Sobre o jogo\n");
	printf("3- Criadores\n");
	printf("4- Sair\n\n");
	scanf("%d", &escolha);

	switch (escolha)
	{
		case 1: // Vai ser destinado a fun��o que ir� salvar as informa��es do usuario na struct
			criarPersonagem(); 
			break;

		case 2:	// Descri��o do jogo
			printf("Jogo de RPG baseado em fatos reais ou nem tanto, inspirado na lend�ria capivara que protegia a humanidade durante anos\n"
				"agora as for�as do meu tentam conquistar os seus poderes para dominar o mundo..."
				"Desenvolvido e criado pela equipe criativa e de desenvolvedores Jose Miguel e Renato Lourenco. \n\n");

			printf("deseja voltar ao jogo?\n\n");
			printf("[SIM: 1]    [SAIR: 2]\n");
			scanf("%d", &escolha);

			if (escolha == 1) // Logica feita para restornar ao menu inicial
			{
				printf("\n");
				main();
			}
			else
			{
				return 0;
			}

			break;

		case 3: // Criadores
			printf("Jose Miguel & Renato Nascimento\n\n");
			printf("deseja voltar ao jogo?\n\n");
			printf("[SIM: 1]    [SAIR: 2]\n");
			scanf("%d", &escolha);

			if (escolha == 1) // Logica feita para restornar ao menu inicial
			{
				printf("\n");
				main();
			}
			else
			{
				return 0;
			}

			break;

		case 4: // Caso a op��o deseja seja a de sair ele encerra o programa
			printf("Saindo...");
			return 0;

		default: // Tratamento de caso a op��o escrita seja diferente das esperadas
			printf("Opcao invalida! Tente novamente.\n\n");
			limparBuffer();
			main();
			printf("\n");
	}

	return 0;
}

// Fun��o para cadastrar o personagem
void criarPersonagem() /*Primeira op��o do menu*/
{
	char nomePersonagem[30];
	int escolhaClasse;
	char classe[10];
	int resposta;

	printf("\nBem-vindo(a) ao Capivara Adventure!\n"
		"Um RPG de acao e comedia como nenhum outro. Sua missao e resgatar\n"
		"a lendaria Capivara Celestial, uma criatura magica e sagrada,\n"
		"sequestrada por Necrotancio, um necromante que planeja usar seus\n"
		"poderes para dominar o mundo. Explore Capivopolis, enfrente inimigos\n"
		"hilarios e desvende segredos absurdos enquanto salva o reino de um\n"
		"destino... peculiar.\n\n\n\n");

	printf("Para comecar, digite o seu nome: ");

	scanf("%s", nomePersonagem);
	strcpy(personagem1.nome, nomePersonagem); /*Armazenar o nome do personagem escolhido na struct (que ser� todo resumo do personagem)*/

	while (escolhaClasse > 3) // Tratamento de caso a op��o escrita seja diferente das esperadas
	{
		printf("\nOla %s escolha a sua classe: \n\n", nomePersonagem);
		printf("1- Guerreiro\n2- Mago\n3- Arqueiro\n\n");
		scanf("%d", &escolhaClasse);

		if (escolhaClasse >= 4)
		{
			printf("Opcao invalida! Tente novamente.\n");
			limparBuffer();
		}
	}

	classeEscolhida(escolhaClasse, classe);	//Fun��o respons�vel pela condi��o da classe, armazenando a escolha e a vari�vel classe
	strcpy(personagem1.classe, classe);

	printf("Otimo, vc escolheu %s\n\n", classe);

	printf("Resumo do personagem: ");

	resumoPersonagem(personagem1.nome, personagem1.classe);	//Chamar a fun��o resumo personagem

	printf("Deseja confirmar?\n\n 1-Sim\n 2-Nao\n\n");
	scanf("%d", &resposta);

	if (resposta != 1)
	{
		criarPersonagem();	//Fun��o de criar personagem ir� repetir at� que o usu�rio confirme a cria��o do personagem*/
	}

	personagemExistente = 1;	//Personagem foi criado, eba

	jogoIniciado(personagem1.nome);
}

// Fun��o destinada a parte da escolha de classes
void classeEscolhida(int escolhaClasse, char *classe)
{
	//Fun��o respons�vel pela escolha da classe, a classe escolhida ser�
	//armazenada no ponteiro classe, que ir� apontar para a var�avel classe em jogar(void)
	if (escolhaClasse == 1)
	{
		strcpy(classe, "Guerreiro");
	}
	else if (escolhaClasse == 2)
	{
		strcpy(classe, "Mago");
	}
	else if (escolhaClasse == 3)
	{
		strcpy(classe, "Arqueiro");
	}
	else
	{
		printf("Opcao invalida! tente novamente.");
	}
}

// Resumo inicial das escolhas feitas
void resumoPersonagem(char *nome, char *classe)
{
	printf("\n\n");
	printf("Nome: %s\n", nome);
	printf("Classe: %s\n", classe);

}

// Inicio do jogo
void jogoIniciado(char *nome)
{ /*Fun��o de gameplay*/
	int resposta;

	checkPoint = 1;	//Esse checkpoint serve tanto para o usuario retornar a esse cen�rio do rpg (Atrav�s da 5 opc�o do MENU) e tanto pra salvar o progresso no FILE
	//O Checkpoint inicial � 1, por�m pra cada cen�rio (func�es) o checkpoint ir� progredir.
	printf("\n====================================================\n");
	printf("\n\nA medida que voce abre os olhos, a luz dourada do entardecer banha as ruas de Capivopolis,\n"
		"uma cidade de arquitetura excentrica e sons vibrantes. O aroma de paes frescos se mistura\n"
		"com o cheiro de pocoes magicas, e o murmurio das conversas nos cafes ecoa pelas calcadas.\n"
		"Voce esta em uma pequena praca, cercado por lojas de artigos magicos, vendedores ambulantes\n"
		"e cidadaos que parecem nao se importar com o caos iminente.\n\n"
		"A sua frente, uma grande estatua de uma Capivara Majestosa, a criatura lendaria que protegeu\n"
		"a cidade por geracoes, observa silenciosamente Capivopolis. Porem, o clima parece diferente hoje.\n"
		"Algo esta no ar.\n\n"
		"Voce sente a tensao crescente. Um pequeno cartaz preso em um poste anuncia um premio\n"
		"substancial para quem resgatar a Capivara Celestial, sequestrada recentemente pelo necromante\n"
		"Necroncito. O rumor e que ele planeja usar o poder da Capivara para invocar um exercito de mortos-\n"
		"vivos e dominar o mundo.\n\n"
		"Agora, sua jornada comeca. O que voce faz?\n\n"

		" 1-Explorar a Cidade\n 2-Analisar a Estatua\n 3-Opcoes\n");

	scanf("%d", &resposta);
	switch (resposta)
	{
		case 1:
		case 2:
			salvarDados(&personagem1, 1);
			explorarCidade(resposta);
			break;

		case 3:
			opcoes();
			printf("\n\n");
			break;

		default:
			printf("Opcao invalida! Tente novamente.\n");
			limparBuffer();
			jogoIniciado(nome);
			printf("\n");
	}
}

// Parte da historia em que o jogador explora a cidade
void explorarCidade(int resposta)
{
	checkPoint = 2;
	//Essa fun��o ser� respons�vel pela exploracao da cidade 

	if (resposta == 1)
	{
		printf("\n====================================================\n");
		printf("\n\nVoce decide explorar as ruas de Capivopolis. A medida que caminha pela cidade, as\n"
			"ruas se tornam cada vez mais movimentadas. As lojas estao cheias de produtos exoticos,\n"
			"e os vendedores gritam ofertas de itens magicos e pocoes raras. Alguns cidadaos o observam\n"
			"com curiosidade, mas todos parecem seguir suas rotinas, indiferentes a crescente tensao\n"
			"causada pelo desaparecimento da Capivara Celestial.\n\n"
			"Voce passa por uma pequena taverna, onde uma musica alegre ecoa de dentro. Apesar do\n"
			"ambiente vibrante, ha uma sensa��o de inquieta�ao, como se todos estivessem tentando\n"
			"ignorar o perigo iminente que ronda a cidade.\n\n");

		char *escolhasCidade[] = { " 1- Entrar na Taverna",
			" 2- Ignorar",
			" 3- Opcoes\n" };

		int respostaCidade = exibirTexto(			"Qual a sua decisao?\n",
			escolhasCidade
	);

		switch (respostaCidade)
		{
			case 1:
				entrarTaverna();
				break;

			case 2:
				printf("**Voce percebe que uma sensacao estranha esta te incomodando e decide entrar na taverna do mesmo jeito.**\n\n");
				entrarTaverna();
				break;

			case 3:
				opcoes();
				printf("\n\n");
				break;

			default:
				printf("Opcao invalida! Tente novamente.\n");
				limparBuffer();
				explorarCidade(resposta);
				printf("\n");
		}
	}
	else if (resposta == 2)
	{
		printf("\n====================================================\n");
		printf("\n\nA sua frente, ergue-se uma imponente estatua, esculpida com detalhes extraordinarios.\n"
			"Ela representa uma capivara majestosa, imortalizada em um pedestal de pedra adornado com runas antigas.\n"
			"Seus olhos de marmore parecem observar atentamente a cidade, com uma expressao serena\n"
			"e ao mesmo tempo cheia de sabedoria. Os detalhes esculpidos mostram uma criatura poderosa\n"
			"e graciosa, refletindo a lenda que ela representa.\n\n"
			"Mas o que chama a atencao, imediatamente, e o objeto curioso que adorna a escultura.\n"
			"Uma reluzente *coroa dourada*, incrustada com gemas que brilham suavemente sob a luz do\n"
			"entardecer, repousa orgulhosamente sobre a cabeca da capivara. Seu design intrincado e delicado\n"
			"e uma obra de arte por si so, com simbolos misticos gravados que parecem irradiar uma\n"
			"leve energia magica. A peca, aparentemente simples, e a verdadeira protagonista da estatuas,\n"
			"conferindo-lhe um toque de misterio e encanto, como se a propria Capivara Celestial,\n"
			"a guardia lendaria, estivesse presente ali, observando e protegendo o mundo que ela inspira.\n\n"
			"A estatua permanece imponente, mas a coroa, com sua beleza e elegancia, atrai todos os\n"
			"olhares, como se aguardasse o momento certo para revelar seu segredo mais profundo.\n\n");

		printf("1- Explorar a cidade\n 2-Permanecer analisando a est�tua\n 3- Opcoes\n\n");
		scanf("%d", &resposta);
		limparBuffer();

		if (resposta == 3)
		{
			opcoes();
		}

		explorarCidade(resposta);
	}
}

// Cenario de entrar na taverna
void entrarTaverna(void)
{
	printf("\n====================================================\n");
	printf("\n\nVoce decide entrar na taverna. O ambiente e acolhedor, com uma luz suave vindo das velas nas mesas.\n"
		"O som de risadas e conversas ecoa pelo salao. Um taverneiro robusto com um avental manchado de vinho,\n"
		"esta limpando um copo atras do balcao. Voce sente o cheiro de carne assada e pao fresco no ar.\n"
		"Um velho anao se aproxima e pergunta: O que voce deseja, aventureiro? Uma bebida quente ou talvez\n"
		"uma conversa interessante?\n\n");

	checkPoint = 3;
	int continuar = 1;	//verdadeiro, serve pro looping do case 1

	while (continuar)
	{
		//Esse while vai fazer o case 1 repetir.

		char *escolhasTaverna[] = {	//As alternativas poss�veis ficar�o armazenadas nessa vari�vel, que � um ponteiro pois ser� usada na vari�vel "respostaTaverna"

			" 1- Bebida",
			" 2- Conversar com o velho anao",
			" 3- Opcoes\n" };

		int respostaTaverna = exibirTexto( // Isto chama a fun��o para mostrar os textos da campanha
			"Qual a sua decisao?\n",
			escolhasTaverna	// Array das escolhas da Taverna
	);

		switch (respostaTaverna)
		{
			case 1:
				printf("\n\nVoce decide tomar uma bebida. Voce sente o forte teor alcoolico descer pela garganta. Isso te faz Cogitar a segunda opcao...\n\n");
				limparBuffer();
				continue;	//A partir daqui, j� que o loop � verdadeiro, ele vai pular todos os cases de baixo (ignora-los e voltar pro inicio do while, at� que o usuario escolha outro case)
				break;
			case 2:
				anaoDialogo();
				break;
			case 3:
				opcoes();
				printf("\n\n");
				break;

			default:
				printf("Opcao invalida! Tente novamente.\n");
				limparBuffer();
				entrarTaverna();
				printf("\n");
		}
	}
}

// Conversa com NPC
void anaoDialogo(void)
{
	printf("\n====================================================\n");
	printf("\n\nAh, aventureiro, tenho algo curioso pra contar. Voce ja ouviu falar da Capivara Magica?\n"
		"Dizem que ela foi abencoada por uma antiga feiticeira e carrega um poder incrivel. Ha pouco\n"
		"tempo, um necromante esquisitao apareceu na regiao e... bom, parece que ele sequestrou\n"
		"a tal capivara. Nao sei o que ele quer com ela, mas desde entao, coisas estranhas vem\n"
		"acontecendo nos arredores. Gente sumindo, gritos nas florestas a noite...\n\n"
		"Ele se inclina mais perto, a voz abaixando para um sussurro. Se voce tiver coragem, ouvi dizer\n"
		"que ele foi visto em uma velha torre ao norte. Talvez queira investigar... ou talvez prefira\n"
		"ficar aqui bebendo. A escolha e sua.\n\n");

	checkPoint = 4;
	int continuar = 1;

	while (continuar)
	{
		char *escolhasAnao[] = { //As alternativas poss�veis ficar�o armazenadas nessa vari�vel, que � um ponteiro pois ser� usada na vari�vel "respostaAnao"

			" 1- Sair para Investigar",
			" 2- Continuar Bebendo",
			" 3- Opcoes\n" };

		int respostaAnao = exibirTexto( // Isto chama a fun��o para mostrar os textos da campanha
			"Qual a sua decisao?\n",
			escolhasAnao // Array das escolhas do anao
	);

		switch (respostaAnao)
		{
			case 1:
				continuar = 0;
				printf("\n====================================================\n");
				printf("\n\nVoce se levanta da cadeira, o olhar decidido.\n"
					"O anao sorri, mostrando dentes amarelados.\n\n"
					"� Corajoso, hein? Aqui, leve isto. � Ele desliza um pequeno frasco de liquido azul.\n"
					"� Pode nao parecer, mas cura ate orgulho ferido.\n\n"
					"Ao sair da taverna, o vento frio da noite corta sua pele.\n"
					"A lua cheia ilumina o caminho, e a silhueta de uma torre antiga surge ao norte,\n"
					"como um dedo ossudo apontando para o ceu.\n"
					"O silencio da floresta e quebrado apenas pelo som de corujas e galhos estalando sob seus passos.\n\n"
					"Conforme voce se aproxima, uma nevoa espessa cobre o chao.\n"
					"Portoes de ferro enferrujados aparecem diante de voce, rangendo como se sussurrassem segredos antigos.\n"
					"La dentro, a velha torre espera, suas janelas negras como olhos vazios.\n\n"
					"De repente, um uivo distante ecoa, seguido por risadas baixas e perturbadoras.\n"
					"Algo � ou alguem � esta ciente de sua presenca.\n\n");
				torreVelha();
				break;
			case 2:

				printf("\n\nVoce decide continuar tomando uma bebida. Voce sente o forte teor alcoolico descer pela garganta. Isso te faz Cogitar a primeira opcao...\n\n");
				limparBuffer();
				continue;
				break;

			case 3:
				opcoes();
				printf("\n\n");
				break;

			default:
				printf("Opcao invalida! Tente novamente.\n");
				limparBuffer();
				anaoDialogo();
				printf("\n");
		}
	}
}

// Cenario da historia passada na torre velha
void torreVelha(void)
{
	checkPoint = 5;
	int continuar = 1;

	while (continuar)
	{
		char *escolhasTorre[] = { // As alternativas poss�veis ficar�o armazenadas nessa vari�vel, que � um ponteiro pois ser� usada na vari�vel "respostaTorre"

			" 1- Procurar uma entrada discreta ao redor da torre",
			" 2- Abrir os portoes com for�a e entrar direto",
			" 3- Opcoes\n" };

		int respostaTorre = exibirTexto( // Isto chama a fun��o para mostrar os textos da campanha
			"Qual a sua decisao?\n",
			escolhasTorre);	// Array das escolhas da torre

		switch (respostaTorre)
		{
			case 1:
				printf("\n====================================================\n");
				printf("\n\nVoce se move pelas sombras, com passos leves, atento a qualquer som ou movimento ao redor.\n"
					"A luz da lua mal consegue atravessar a nevoa densa, mas voce avista algo ao redor da torre:\n"
					"uma pequena porta de madeira parcialmente escondida por trepadeiras.\n\n"
					"Quando se aproxima, percebe que a porta esta trancada com um cadeado enferrujado.\n"
					"Ao lado dela, ha um buraco na parede, estreito, mas talvez o suficiente para voce passar �\n"
					"embora pareca perigoso.\n\n"
					"Enquanto decide o que fazer, um ruido subito surge atras de voce: passos apressados quebrando galhos.\n"
					"Alguem � ou alguma coisa � esta vindo!\n\n");
				entrarBuraco();
				break;

			case 2:
				printf("\n\nVoce reune toda a sua forca, posiciona-se para empurrar os portoes enferrujados e...\n"
					"com um estrondo, seus musculos come�am a ceder. O ferro resiste, e voce, exausto e sem sucesso,\n"
					"fica mais uma vez de frente aos portoes implacaveis. O barulho atrai a atencao de algo nas sombras.\n"
					"Voce se sente um pouco mais vulneravel agora.\n\n");

				limparBuffer();
				continue;
				break;

			case 3:
				opcoes();
				printf("\n\n");
				break;

			default:
				printf("Opcao invalida! Tente novamente.\n");
				limparBuffer();
				torreVelha();
				printf("\n");
		}
	}
}

// Cenario que ao chegar a torre entra-se no local por uma entrada discreta
void entrarBuraco(void)
{
	checkPoint = 6;

	char *escolhasBuraco[] = {	// As alternativas poss�veis ficar�o armazenadas nessa vari�vel, que � um ponteiro pois ser� usada na vari�vel "respostaBuraco"

		" 1- Entrar pelo buraco na parede, apesar do perigo.",
		" 2- Esconder-se nas trepadeiras, esperando para emboscar quem esta vindo.",
		" 3- Opcoes" };

	int respostaBuraco = exibirTexto( // Isto chama a fun��o para mostrar os textos da campanha
		"Qual a sua decisao?\n",
		escolhasBuraco // Array das escolhas do Buraco
);

	switch (respostaBuraco)
	{
		case 1:
			printf("\n====================================================\n");
			printf("\n\nVoce decide que o risco vale a pena e se aproxima do buraco na parede.\n"
				"Com um esforco, consegue se esgueirar pelo pequeno espaco, sentindo as pedras frias e irregulares da parede em suas costas.\n"
				"Apos alguns momentos de desconforto, voce emerge em uma camara escura e umida, onde o ar e pesado e estagnado.\n\n"
				"O silencio e perturbador, mas algo nao parece certo. A camara a sua frente esta vazia, exceto por um antigo altar no centro,\n"
				"coberto de musgo e poeira. Voce se aproxima, mas ao colocar a mao na superficie do altar, ouve um estrondo atras de si.\n"
				"A porta pela qual voce passou comeca a se fechar sozinha, e voce escuta passos se aproximando na escuridao!\n\n"
				"O que voce faz?\n");

			olharParaTras();
			break;

		case 2:
			printf("\n====================================================\n");
			printf("\n\nVoce se agacha rapidamente, movendo-se com cautela ate se esconder nas trepadeiras densas.\n"
				"As folhas arranham sua pele, mas voce consegue se camuflar bem o suficiente para ficar invisivel.\n"
				"Voce aguarda, os minutos passam e o silencio se torna ainda mais desconfortavel.\n"
				"O barulho dos passos parece ter desaparecido, e nada se move na direcao da torre.\n"
				"O que antes parecia uma ameaca iminente agora soa apenas como uma lembranca distante.\n\n"
				"Voce estica o pescoco e observa ao redor, mas nao ve nenhuma figura se aproximando.\n"
				"O ar esta denso, e a sensacao de que algo esta errado persiste, mas ninguem aparece.\n"
				"A espera comeca a se arrastar, e a tensao cresce com o tempo que se estende sem resposta. Voce decide descer...\n\n");

			entrarBuraco();
			break;
		case 3:
			opcoes();
			printf("\n\n");
			break;

		default:
			printf("Opcao invalida! Tente novamente.\n");
			limparBuffer();
			entrarBuraco();
			printf("\n");
	}
}

// Cenario em que o vilao aparece
void olharParaTras(void)
{
	checkPoint = 7;

	char *escolhasOlharAtras[] = {	//As alternativas poss�veis ficar�o armazenadas nessa vari�vel, que � um ponteiro pois ser� usada na vari�vel "respostaBuraco"

		" 1- Virar para tras e encarar o que esta vindo.",
		" 2- Correr em direcao ao altar e tentar interagir com ele, na esperan�a de ativar algo ou encontrar uma saida.",
		" 3- Opcoes\n" };

	int respostaOlharAtras = exibirTexto(// Isto chama a fun��o para mostrar os textos da campanha
		"Qual a sua decisao?\n",
		escolhasOlharAtras	// Array das escolhas da Taverna
);

	switch (respostaOlharAtras)
	{
		case 1:
			printf("\n====================================================\n");
			printf("\n\nVoce se vira rapidamente, encarando a escuridao. Uma figura alta e encurvada emerge, envolta em um manto negro que parece feito de sombras vivas.\n"
				"Olhos vermelhos brilham por baixo do capuz, e um cajado decorado com caveiras emite uma luz purpura assustadora.\n"
				"Uma voz rouca ecoa: 'Quem ousa invadir minha camara?' Enquanto ele ergue o cajado, o ar parece congelar ao seu redor.\n\n"
				"De repente, ele tropeca, o cajado cai no chao e o capuz escorrega, revelando... um velhinho magricelo com um bigode torto e oculos quebrados.\n"
				"'Ai, minhas costas!', ele reclama com uma voz fina e esgani�ada. 'Eu sou Necroncito, o Pequeno e Infame! Agora diga, o que faz na MINHA torre?'\n");
			break;

		case 2:
			printf("\n====================================================\n");
			printf("\n\nVoce corre em direcao ao altar, sentindo o frio crescer ao tocar os simbolos sinistros na superficie.\n"
				"A sala vibra, e uma abertura comeca a se formar atras do altar. Mas, de repente, uma voz rouca ecoa: 'Achou que poderia escapar tao facilmente?'\n"
				"Uma figura encapuzada emerge das sombras, com olhos vermelhos brilhando e um cajado ameacador. O ar se congela ao redor de voce.\n\n"
				"Quando ele levanta o cajado, trope�a, derrubando-o no chao. O capuz cai, revelando um velhinho magricelo com oculos tortos e um bigode esquisito.\n"
				"'Ai, minhas costas!', ele reclama, e voce percebe que e Necroncito, o Pequeno e Infame, tentando manter a pose ameacadora. Agora diga, o que faz na MINHA torre?\n\n");

			break;
		case 3:
			opcoes();
			break;

		default:
			printf("Opcao invalida! Tente novamente.\n");
			limparBuffer();
			olharParaTras();
			printf("\n");
	}

	printf("\n====================================================\n");
	printf("                FIM DO BETA\n");
	printf("====================================================\n");
	printf("\nA jornada at� aqui foi cheia de desafios e surpresas!\n");
	printf("Com isso, encerramos a fase Beta do Capivara Adventure.\n");
	printf("Obrigado Professor Mayrton por nos ajudar a tornar essa aventura ainda mais Unica!\n");
	printf("\n====================================================\n");

	printf("Desenvolvido por: Jose Miguel & Renato Nascimento\n");

	exit(0);
}

// Menu que fica acessivel durante o jogo
void opcoes(void)
{
	pntr = &personagem1;

	char *escolhasOpcoes[] = {	//As alternativas poss�veis ficar�o armazenadas nessa vari�vel, 

		" 1- Sobre o Jogo",
		" 2- Sobre o Personagem",
		" 3- Resetar Personagem",
		" 4- Abrir Loja",
		" 5- Abrir Mochila",
		" 6- Voltar ao jogo",
		" 7- Sair do jogo\n",
	};

	int respostaOpcoes = exibirTextoOpcoes(//O exibirTexto � a funcao respons�vel tanto por pegar esse texto ""O que deseja fazer?\n", quanto pra ser usado como base pro switch (respostaOpcoes)
		"O que deseja fazer?\n",
		escolhasOpcoes	//� o array das opcoes
);

	switch (respostaOpcoes)
	{
		//Isso pega a resposta do usuario (que foi escaneada no exibir texto)
		case 1:
			printf("Jogo de RPG baseado em fatos reais ou nem tanto, inspirado na lend�ria capivara que protegia a humanidade durante anos\n"
				"agora as for�as do meu tentam conquistar os seus poderes para dominar o mundo..."
				"Desenvolvido e criado pela equipe criativa e de desenvolvedores Jose Miguel e Renato Lourenco.\n\n");
				
			//Fazer voltar pra onde estava
			break;
		case 2:
			buscarPersonagem(pntr, 1);
			break;
		case 3:
			removerPersonagem();
			break;
		case 4:
			loja();
			break;

		case 5:
			listarMochila(inventario, tamanhoInventario);	//o valor de  tamanhoInvent�rio � copiado pro parametro tamanho, por isso que ao inv�s de apenas TAMANhO como parametro, usamos o tamanhoInventario
			break;

		case 6:
			retornarJogo();
			break;

		case 7:
			printf("Saindo...");
			salvarDados(&personagem1, 1);
			exit(0);

		default:
			printf("Opcao invalida! Tente novamente.\n");
			limparBuffer();
			opcoes();
			printf("\n");
	}

	opcoes();
}

// Funcao respons�vel por exibir os textos, assim como as escolhas nos dialogos.
int exibirTexto(char *descricao, char *escolhas[])
{
	
	int i;	// Para itera��o
	int opcao;	// Pra opcao a ser escaneada

	printf("%s\n", descricao);

	for (i = 0; i < 3; i++)
	{
		printf("%s\n", escolhas[i]);	// Esse laco de repeti��o, far� com que as escolhas sejam impressas
	}

	scanf("%d", &opcao);	// 

	return opcao;	// vai pegar a opcao escolhida pelo usuario 
}

// Funcao respons�vel por exibir os textos, assim como as escolhas nos dialogos.
int exibirTextoOpcoes(char *descricao, char *escolhas[])
{
	
	int i;	// Para itera��o
	int opcao;	// Pra opcao a ser escaneada

	printf("%s\n", descricao);

	for (i = 0; i < 7; i++)
	{
		printf("%s\n", escolhas[i]);	// Esse laco de repeti��o, far� com que as escolhas sejam impressas
	}

	scanf("%d", &opcao);	// 

	return opcao;	// vai pegar a opcao escolhida pelo usuario 
}

// Remove o personagem 
void removerPersonagem()
{
	int resposta;

	printf("\nRemovendo Personagem '%s'...\n", personagem1.nome);

	// "Reseta" os dados do personagem
	strcpy(personagem1.nome, "");	//Nome foi zerado
	personagem1.nivel = 0;	//Nivel tbm
	personagem1.exp = 0.0;	//xp tbm
	strcpy(personagem1.classe, "");	// o msm com a classe

	personagemExistente = 0;	// nao existe mais personagem
	printf("Personagem removido com sucesso.\n");
	printf("Deseja Reiniciar o Game?\n 1- Sim\n 2- Nao\n");
	scanf("%d", &resposta);
	if (resposta == 1)
	{
		main();
	}
	else if (resposta == 2)
	{
		opcoes();
	}
}

// Funcao pra buscar e listar personagens
void buscarPersonagem(Personagem *personagemArray, int contagem)
{
	
	personagem1.nivel = 1;
	char personagemNome[20];

	printf("Digite o nome do personagem: ");
	scanf("%s", personagemNome);

	int i;

	for (i = 0; i < contagem; i++)
	{
		if (strcmp(personagemArray[i].nome, personagemNome) == 0)	// Para se comparar o conte�do de dois strings deve usar a fun��o strcmp
		{
			printf("\n-------------------------------------\n");
			printf("\nPersonagem Encontrado!\n\n");
			printf("\nNome: %s\n", personagemArray[i].nome);
			printf("\nNivel atual: %d\n", personagemArray[i].nivel);
			printf("\nClasse %s\n", personagemArray[i].classe);
			printf("\n-------------------------------------\n");
		}
		else
		{
			printf("N�o encontrando!\n");
		}
	}
}

// Inserir os itens na mochila
void inserirElemento(char inventario[][20], int *tamanho, const char *item)
{
	if (*tamanho < MAX_INVENTARIO)
	{
		// Se o tamanho atual for maior que o tamanho m�ximo (10)
		strcpy(inventario[*tamanho], item);	// Vai inserir no inventario (no tamanho atual) o item
		(*tamanho) ++;	// Vai aumentar o tamanho do inventario atual (para nao ultrapassar o limite de itens)
	}
	else
	{
		printf("Invent�rio cheio! N�o � poss�vel adicionar mais itens.\n");
	}
}

// Listar itens da mochila
void listarMochila(char inventario[][20], int tamanho)
{
	int i;
	printf("\n-------------------------------------\n");
	printf("Mochila: \n");
	for (i = 0; i < tamanho; i++ )// Enquanto o i for menor que o tamanho maximo (que � 10), ele vai imprimindo os itens do inventario
	{
		printf("\n %s\n", inventario[i]);
	}

	printf("\n-------------------------------------\n");
}

// Cenario do jogo em que o jogador vai ter a op��o de comprar os objetos
void loja()
{
	
	int escolha;

	printf("Bem vindo(a) a nossa loja, aventureiro(a). Escolha uma das opcoes abaixo:\n\n");
	printf("Conhe�a nossos itens\n");
	printf("1- Mapa\n");
	printf("2- Bussola\n");
	printf("3- Armadura\n");
	printf("4- Po magico\n");
	printf("5- Pocao de vida\n");
	printf("6- Voltar para o jogo\n\n");
	scanf("%d", &escolha);
	
	switch (escolha) // Os cases a seguir ser� destinado a confirma��o de cada item
	{

		case 1:
			printf("deseja confirmar a compra?\n");
			printf("[SIM: 1]    [SAIR: 2]\n");
			scanf("%d", &escolha);

			if (escolha == 1)
			{
				printf("Obrigado pela preferencia. Volte sempre!\n");
				inserirElemento(inventario, &tamanhoInventario, "Mapa");
			}
			else
			{
				void loja();
			}

			break;

		case 2:
			printf("deseja confirmar a compra?\n");
			printf("[SIM: 1]    [SAIR: 2]\n");
			scanf("%d", &escolha);

			if (escolha == 1)
			{
				printf("Obrigado pela preferencia. Volte sempre!\n");
				inserirElemento(inventario, &tamanhoInventario, "Bussola");
			}
			else
			{
				void loja();
			}

			break;

		case 3:
			printf("deseja confirmar a compra?\n");
			printf("[SIM: 1]    [SAIR: 2]\n");
			scanf("%d", &escolha);

			if (escolha == 1)
			{
				printf("Obrigado pela preferencia. Volte sempre!\n");
				inserirElemento(inventario, &tamanhoInventario, "Armadura");
			}
			else
			{
				void loja();
			}

			break;

		case 4:
			printf("deseja confirmar a compra?\n");
			printf("[SIM: 1]    [SAIR: 2]\n");
			scanf("%d", &escolha);

			if (escolha == 1)
			{
				printf("Obrigado pela preferencia. Volte sempre!\n");
				inserirElemento(inventario, &tamanhoInventario, "Po magico");
			}
			else
			{
				void loja();
			}

			break;

		case 5:
			printf("deseja confirmar a compra?\n");
			printf("[SIM: 1]    [SAIR: 2]\n");
			scanf("%d", &escolha);

			if (escolha == 1)
			{
				printf("Obrigado pela preferencia. Volte sempre!\n");
				inserirElemento(inventario, &tamanhoInventario, "Pocao de vida");
			}
			else
			{
				void loja();
			}

			break;

		case 6:
			printf("deseja retornar?\n");
			printf("[SIM: 1]    [SAIR: 2]\n");
			scanf("%d", &escolha);

			if (escolha == 1)
			{
				printf("Volte sempre!\n");
				entrarTaverna();
			}
			else
			{
				void loja();
			}

			break;
		default:
			printf("Opcao invalida! Tente novamente.\n");
			void loja();
			printf("\n");
	}
}

// Faz com que o usu�rio retorne na fun��o que estava
void retornarJogo()
{
	
	switch (checkPoint)
	{
		case 1:
			// Estado inicial do jogo
			jogoIniciado(personagem1.nome);
			break;

		case 2:
			// No cen�rio da explora��o da cidade
			explorarCidade(1);	// Passa 1 como padr�o para continuar explorando
			break;

		case 3:
			//No cen�rio da taverna
			entrarTaverna();
			break;

		case 4:
			//No dialogo do anao
			anaoDialogo();
			break;

		case 5:
			//No cenario da torre
			torreVelha();
			break;

		case 6:
			//No cen�rio quando entra no buraco da torre
			entrarBuraco();
			break;

		case 7:
			//No cen�rio quando olha para tr�s
			olharParaTras();
			break;

		default:
			printf("Erro: Checkpoint inv�lido\n");
			break;
	}
}

/*
*
* Contemos os requisitos da atividade:
*
* #Inserir elemento   
* #Deletar elemento      
* #Buscar elemento       
* #Listar elemento       
* #Atualizar elemento    
* #Livre                 
*
* Com nomes diferentes e que fazem sentido com nosso tema. 
* 
* 
* Agradecemos a sua dedica��o em nos ensinar mestre! Boas festa e feliz ano novo. 
*
*/