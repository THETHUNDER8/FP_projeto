/*
***********************************************************************************************
*Trabalho para Fundamentos de programação
*Trabalho realizado por:Hugo Ferreira Gonçalves nº2220891
*                     e: Duarte Luis Miguel Ferreira nº2220871
*
*Trabalho realizado dia:14/1/2023
**********************************************************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#define MAX_PARTICIPANTES 5000
#define MAX_ATIVIDADES 200
#define MAX_INSCRICOES 10000
#define MAX_CARATERES 80
//Estrutura de dados dos participantes
typedef struct
{
    int ID_participante;
    char nome[MAX_CARATERES];
    int escola;
    int NIF;
    char email[MAX_CARATERES];
    int contacto;
} t_participantes;
//estrutura de dados da data e da hora
typedef struct
{
    int dia,mes,ano, hora,minuto,segundo;
} t_data_hora;
//estrutura de dados das atividades
typedef struct
{
    int ID_atividade;
    char designacao_atividade[MAX_CARATERES];
    t_data_hora data_hora_atividade;
    char local_atividade[MAX_CARATERES];
    int tipo_atividade;
    int AE_organizadora;
    float valor_inscricao;
} t_atividade;
//estrutura de dados das incriões
typedef struct
{
    int ID_inscricao;
    int ID_participante_inscricao;
    int ID_atividade_inscricao;
    float valor_pago;
    t_data_hora data_hora_inscricao;

} t_inscricao;

//funções de resgisto e consulta de dados
int registar_participante(t_participantes v_participante[],int numero_participantes);
void consultar_participantes(t_participantes v_participante[],int numero_participantes);
int resgistar_atividade(t_atividade v_atividade[],int numero_atividades);
void consultar_atividades(t_atividade v_atividade[],int numero_atividades);
int registar_inscricao(t_inscricao v_inscricao[],t_participantes v_participante[],t_atividade v_atividade[],int numero_inscricoes,int numero_participantes,int numero_atividades);
void consultar_incricoes (t_inscricao v_inscricao[], int numero_inscricoes);
//Funções estatisticas
void n_atividades_associacao(t_atividade v_atividade[],int numero_atividades);
void percentagem_inscricoes_escola(t_participantes v_participante[],t_inscricao v_incricao[],int numero_inscricoes);
void horizonte_temporal();
//Funções de leitura e gravação de ficheiros
void gravar_fichero_participantes(t_participantes v_participante[], int numero_participantes);
void gravar_fichero_atividades(t_atividade v_atividade[], int numero_atividades);
void gravar_fichero_inscricoes(t_inscricao v_inscricao[], int numero_inscricoes);
int ler_ficheiro_participantes(t_participantes v_participante[]);
int ler_ficheiro_atividades(t_atividade v_atividade[]);
int ler_ficheiro_inscricoes (t_inscricao v_inscricao[]);
//Funções com apenas um objetivo
int procura_NIF(t_participantes v_participante[], int tamanho,int min, int max);
int procura_contacto(t_participantes v_participante[], int tamanho,int min, int max);
int procura_ID_participante(t_participantes v_participante[], int tamanho,int min, int max);
int procura_ID_atividade(t_atividade v_atividade[], int tamanho,int min, int max);
int registo_duplicado(t_inscricao v_inscricao[], int tamanho,int id_participante, int id_atividade);
void data_hora_atual(t_data_hora *data_hora);
int ler_numero(char *texto,int min, int max);
float ler_preco(char *texto,int min, int max);
char ler_string(char *texto,char *string, char char1, char char2);
int menu_opcoes();
int menu_ficheiros();
char confirma_saida();

int main()
{
    int op_ficheiro,op,total_participantes=0,total_atividades=0, total_inscricoes=0;
    char sair,sair_ficheiros;
    t_participantes v_participante[MAX_PARTICIPANTES];
    t_atividade v_atividade[MAX_ATIVIDADES];
    t_inscricao v_inscricao[MAX_INSCRICOES];
    t_data_hora comp_data1;
    t_data_hora comp_data2;
    setlocale(LC_ALL,"Portuguese");
    do
    {
        op=menu_opcoes();
        fflush(stdin);
        switch(op)
        {
        case 1:
            if(total_participantes>=MAX_PARTICIPANTES)
            {
                system("cls");
                printf("\nERRO:numero de estudantes ultrapassado!");
            }
            else
                total_participantes=registar_participante(v_participante,total_participantes);
            getchar();
            system("cls");
            break;
        case 2:
            if (total_participantes == 0)
            {
                system("cls");
                printf("\nErro: Nao foram inseridos Participantes!\n");
            }
            else
                consultar_participantes(v_participante,total_participantes);
            getchar();
            system("cls");
            break;
        case 3:
            if(total_atividades>=MAX_ATIVIDADES)
            {
                system("cls");
                printf("\nERRO:Numero de atividades ultrapassado!");
            }
            else
                total_atividades=resgistar_atividade(v_atividade, total_atividades);
            getchar();
            system("cls");
            break;
        case 4:
            if (total_atividades == 0)
            {
                system("cls");
                printf("\nErro: Nao foram inseridas atividades!\n");
            }
            else
                consultar_atividades(v_atividade, total_atividades);
            getchar();
            system("cls");
            break;
        case 5:
            if(total_inscricoes>=MAX_INSCRICOES)
            {
                system("cls");
                printf("\nERRO:Numero de inscricoes ultrapassado!");
            }
            else
                total_inscricoes=registar_inscricao(v_inscricao,v_participante,v_atividade, total_inscricoes,total_participantes,total_atividades);
            getchar();
            system("cls");
            break;
        case 6:
            if (total_inscricoes == 0)
            {
                system("cls");
                printf("\nErro: Nao foram feitas inscrições!\n");
            }
            else
                consultar_incricoes(v_inscricao, total_inscricoes);
            getchar();
            system("cls");

            break;
        case 7:
            if(total_atividades>0)
                n_atividades_associacao( v_atividade,total_atividades);
            else
                printf("\nERRO: sem atividades");
            if(total_participantes>0 || total_inscricoes >0)
                percentagem_inscricoes_escola(v_participante,v_inscricao, total_inscricoes);
            else
                printf("\nERRO: sem participantes ou sem incricoes");
            if (total_inscricoes>0)
            {
                    printf("\nValor total das inscrições entre duas datas (horizonte temporal) por tipo de atividade(inclusivo)\n");
                    printf("\nPrimeira data:");
                    comp_data1.dia=ler_numero("\nDia :",1,31);
                    comp_data1.mes=ler_numero("\nMes :",1,12);
                    comp_data1.ano=ler_numero("\nAno :",2023,2050);
                    printf("\nSegunda data:");
                    comp_data2.dia=ler_numero("\nDia :",1,31);
                    comp_data2.mes=ler_numero("\nMes :",1,12);
                    comp_data2.ano=ler_numero("\nAno :",2023,2050);
                printf("Valor total das inscrições entre duas datas (horizonte temporal) por tipo de atividade(inclusivo)");
                horizonte_temporal(comp_data1, comp_data2 ,v_inscricao,v_atividade,total_inscricoes);
                printf("\n********************************************************\n");
            }
            else
                printf("\nERRO: sem inscrições");

            break;
        case 8:
            do
            {
                system("cls");
                op_ficheiro=menu_ficheiros();
                fflush(stdin);
                switch(op_ficheiro)
                {
                case 1:
                    total_participantes = ler_ficheiro_participantes(v_participante);
                    total_atividades = ler_ficheiro_atividades(v_atividade);
                    total_inscricoes = ler_ficheiro_inscricoes(v_inscricao);
                    getchar();
                    break;
                case 2:
                    if (total_participantes == 0)
                        printf("\nErro: Nao foram inseridos paticipantes!\n");
                    else
                        gravar_ficheiro_participantes(v_participante, total_participantes);
                    if(total_atividades == 0)
                        printf("\nErro: Nao foram inseridas atividades!\n");
                    else
                        gravar_ficheiro_atividades(v_atividade, total_atividades);
                    if(total_inscricoes == 0)
                        printf("\nErro: Nao foram inseridas incrições!\n");
                    else
                        gravar_ficheiro_inscricoes(v_inscricao, total_inscricoes);
                    getchar();
                    break;
                case 0:
                    sair_ficheiros=confirma_saida();
                    break;
                }
            }
            while(sair_ficheiros!='S');
            break;
        case 0:
            sair=confirma_saida();
            break;
        }
    }
    while(sair!='S');

    return 0;
}
//resgista um participante
int registar_participante(t_participantes v_participante[],int numero_participantes)
{
    char string[MAX_CARATERES]= {'\0'};
    v_participante[numero_participantes].ID_participante=numero_participantes;
    ler_string("\nInsira o nome do participante:",string,'\0','\0');
    strcpy(v_participante[numero_participantes].nome, string);
    v_participante[numero_participantes].escola=ler_numero("\n1-ESTG|2-ESECS|3-ESAD|4-ESTM|5-ESSLei\nInsira a escola a que pretence:",1,5);
    procura_NIF(v_participante, numero_participantes,100000000,999999999);
    procura_contacto(v_participante,numero_participantes,900000000,999999999);
    ler_string("\nInsira o email do participante:",string,'@','.');
    strcpy(v_participante[numero_participantes].email, string);
    numero_participantes=numero_participantes+1;
    getchar();
    return numero_participantes;
}
//mostra os participantes registados
void consultar_participantes(t_participantes v_participante[],int numero_participantes)
{
    int indice;
    system("cls");
    printf("\nDados dos Participantes\n");
    for (indice = 0; indice < numero_participantes; indice++)
    {
        printf("\n ID do Participante:%d\n Nome:%s\n Escola(1-ESTG|2-ESECS|3-ESAD|4-ESTM|5-ESSLei):%d\n NIF:%d\n Email:%s\n Contacto:%d\n", v_participante[indice].ID_participante,v_participante[indice].nome, v_participante[indice].escola
               ,v_participante[indice].NIF,v_participante[indice].email,v_participante[indice].contacto);
        printf("*************************************");
    };
}
//resgista uma atividade
int resgistar_atividade(t_atividade v_atividade[],int numero_atividades)
{
    char string[MAX_CARATERES]= {'\0'};
    v_atividade[numero_atividades].ID_atividade=numero_atividades;
    ler_string("\nInsira a designação da atividade:",string,'\0','\0');
    strcpy(v_atividade[numero_atividades].designacao_atividade, string);
    v_atividade[numero_atividades].data_hora_atividade.dia=ler_numero("\nDia :",1,31);
    v_atividade[numero_atividades].data_hora_atividade.mes=ler_numero("\nMes :",1,12);
    v_atividade[numero_atividades].data_hora_atividade.ano=ler_numero("\nAno :",2023,2050);
    v_atividade[numero_atividades].data_hora_atividade.hora=ler_numero("\nHora :",0,23);
    v_atividade[numero_atividades].data_hora_atividade.minuto=ler_numero("\nMinutos :",0,59);
    ler_string("\nInsira o local da atividade:",string,'\0','\0');
    strcpy(v_atividade[numero_atividades].local_atividade, string);
    v_atividade[numero_atividades].tipo_atividade=ler_numero("\n1-Académica|2-Lazer|3-Cultura|4-Desporto|5-Formação|6-Outra\nInsira o tipo de atividade :",1,6);
    v_atividade[numero_atividades].AE_organizadora=ler_numero("\n1-AE-ESTG|2-AE-ESECS|3-AE-ESAD|4-AE-ESTM|5-AE-ESSLei\nInsira a Associação de Estudantes organizadora da atividade:",1,5);
    v_atividade[numero_atividades].valor_inscricao=ler_preco("\nValor da inscrição:",0,999);
    numero_atividades=numero_atividades+1;
    getchar();
    return numero_atividades;
}
//mostra as atividades registadas
void consultar_atividades(t_atividade v_atividade[],int numero_atividades)
{
    int indice;
    system("cls");
    printf("\nConsultar Atividades\n");
    for (indice = 0; indice < numero_atividades; indice++)
    {
        printf("\n ID da Atividade:%d\n Designação da atividade:%s\n Data da atividade:%d-%d-%d\n Hora da atividade:%d:%d\n Local da Atividade:%s\n Tipo de atividade(1-Académica|2-Lazer|3-Cultura|4-Desporto|5-Formação|6-Outra):%d\n AE-Organizadora(1-AE-ESTG|2-AE-ESECS|3-AE-ESAD|4-AE-ESTM|5-AE-ESSLei):%d\n Valor da Inscrição:%2.f\n ",
               v_atividade[indice].ID_atividade,v_atividade[indice].designacao_atividade,v_atividade[indice].data_hora_atividade.dia, v_atividade[indice].data_hora_atividade.mes,v_atividade[indice].data_hora_atividade.ano
               ,v_atividade[indice].data_hora_atividade.hora,v_atividade[indice].data_hora_atividade.minuto,v_atividade[indice].local_atividade,v_atividade[indice].tipo_atividade,v_atividade[indice].AE_organizadora,v_atividade[indice].valor_inscricao);
        printf("*************************************");
    };
}

//resgista uma incrição
int registar_inscricao(t_inscricao v_inscricao[],t_participantes v_participante[],t_atividade v_atividade[],int numero_inscricoes,int numero_participantes,int numero_atividades)
{
    int participante_id,atividade_id,duplicado_index;
    v_inscricao[numero_inscricoes].ID_inscricao=numero_inscricoes;
    //confirma se existe uma incrição duplicada
    do
    {
        participante_id=procura_ID_participante(v_participante,numero_participantes,0,numero_participantes-1);
        atividade_id=procura_ID_atividade(v_atividade,numero_atividades,0,numero_atividades-1);
        duplicado_index=registo_duplicado(v_inscricao,numero_inscricoes,participante_id,atividade_id);
        if (duplicado_index!=-1)
            printf("\nErro:inscrição duplicada!");
        else
        {
            v_inscricao[numero_inscricoes].ID_participante_inscricao=participante_id;
            v_inscricao[numero_inscricoes].ID_atividade_inscricao=atividade_id;
        }
    }
    while(duplicado_index!=-1);
    v_inscricao[numero_inscricoes].valor_pago=ler_preco("\nValor da inscrição:",0,999);
    data_hora_atual(&v_inscricao[numero_inscricoes].data_hora_inscricao);
    numero_inscricoes=numero_inscricoes+1;
    getchar();
    return numero_inscricoes;
}
//mostra as incrições registadas
void consultar_incricoes (t_inscricao v_inscricao[], int numero_inscricoes)
{
    int indice;
    system("cls");
    printf("\nDados das Inscriçoes\n");
    for (indice = 0; indice < numero_inscricoes; indice++)
    {
        printf("\n ID da inscricao:%d\n ID do participante:%d\n ID da atividade:%d\n Valor Pago:%0.f\n Data :%d-%d-%d\n Hora :%d:%d:%d\n", v_inscricao[indice].ID_inscricao,v_inscricao[indice].ID_participante_inscricao, v_inscricao[indice].ID_atividade_inscricao,v_inscricao[indice].valor_pago
               ,v_inscricao[indice].data_hora_inscricao.dia, v_inscricao[indice].data_hora_inscricao.mes,v_inscricao[indice].data_hora_inscricao.ano, v_inscricao[indice].data_hora_inscricao.hora,v_inscricao[indice].data_hora_inscricao.minuto, v_inscricao[indice].data_hora_inscricao.segundo);
        printf("*************************************");
    }
}
//numero de atividades realizadas por associação
void n_atividades_associacao(t_atividade v_atividade[],int numero_atividades)
{
    float contador_escola1=0,contador_escola2=0,contador_escola3=0,contador_escola4=0,contador_escola5=0;
    int indice=0;

    for(indice=0; indice<numero_atividades; indice++)
    {
        if(v_atividade[indice].AE_organizadora==1)
            contador_escola1=contador_escola1+1;
        if(v_atividade[indice].AE_organizadora==2)
            contador_escola2=contador_escola2+1;
        if(v_atividade[indice].AE_organizadora==3)
            contador_escola3=contador_escola3+1;
        if(v_atividade[indice].AE_organizadora==4)
            contador_escola4=contador_escola4+1;
        if(v_atividade[indice].AE_organizadora==5)
            contador_escola5=contador_escola5+1;
    }
    printf("Numero de atividades realizadas por associação");
    printf("\n1-AE-ESTG:%0.f-%1.f%%\n2-AE-ESECS:%0.f-%1.f%%\n3-AE-ESAD:%0.f-%1.f%%\n4-AE-ESTM:%0.f-%1.f%%\n5-AE-ESSLei:%0.f-%1.f%%\n",contador_escola1,(contador_escola1/numero_atividades)*100,contador_escola2,contador_escola2/numero_atividades*100,
           contador_escola3,contador_escola3/numero_atividades*100,contador_escola4,contador_escola4/numero_atividades*100,contador_escola5,contador_escola5/numero_atividades*100);
    printf("\n********************************************************\n");
}
//Percentagem de inscrições por escola
void percentagem_inscricoes_escola(t_participantes v_participante[],t_inscricao v_incricao[],int numero_inscricoes)
{
    float percentagem_escola1=0,percentagem_escola2=0,percentagem_escola3=0,percentagem_escola4=0,percentagem_escola5=0;
    int indice=0;

    for(indice=0; indice<numero_inscricoes; indice++)
    {
        if(v_participante[v_incricao[indice].ID_participante_inscricao].escola == 1)
            percentagem_escola1=percentagem_escola1+1;
        if(v_participante[v_incricao[indice].ID_participante_inscricao].escola == 2)
            percentagem_escola2=percentagem_escola2+1;
        if(v_participante[v_incricao[indice].ID_participante_inscricao].escola == 3)
            percentagem_escola3=percentagem_escola3+1;
        if(v_participante[v_incricao[indice].ID_participante_inscricao].escola == 4)
            percentagem_escola4=percentagem_escola4+1;
        if(v_participante[v_incricao[indice].ID_participante_inscricao].escola == 5)
            percentagem_escola5=percentagem_escola5+1;
    }
        printf("Percentagem de inscrições por escola");
        printf("\n1-ESTG:%0.f-%1.f%%\n2-ESECS:%0.f-%1.f%%\n3-ESAD:%0.f-%1.f%%\n4-ESTM:%0.f-%1.f%\n5-ESSLei:%0.f-%1.f%%\n",percentagem_escola1,(percentagem_escola1/numero_inscricoes)*100,percentagem_escola2,percentagem_escola2/numero_inscricoes*100,
               percentagem_escola3,percentagem_escola3/numero_inscricoes*100,percentagem_escola4,percentagem_escola4/numero_inscricoes*100,percentagem_escola5,percentagem_escola5/numero_inscricoes*100);
        printf("\n********************************************************\n");
}
//Valor total das inscrições entre duas datas(inclusivo) por tipo de atividade
void horizonte_temporal(t_data_hora data1, t_data_hora data2 ,t_inscricao v_incricao[],t_atividade v_atividade[],int numero_incricoes)
{
    float atividade1=0,atividade2=0,atividade3=0,atividade4=0,atividade5=0,atividade6=0,soma_atividades=0;
    int indice=0;
    for(indice=0;indice<numero_incricoes;indice++)
    {
        if(data1.ano<=v_incricao[indice].data_hora_inscricao.ano && data2.ano>= v_incricao[indice].data_hora_inscricao.ano && data1.mes<=v_incricao[indice].data_hora_inscricao.mes && data2.mes>= v_incricao[indice].data_hora_inscricao.mes && data1.dia<=v_incricao[indice].data_hora_inscricao.dia && data2.dia>= v_incricao[indice].data_hora_inscricao.dia)
            {
                if(v_atividade[v_incricao[indice].ID_atividade_inscricao].tipo_atividade == 1)
                    atividade1=atividade1+v_incricao[indice].valor_pago;
                if(v_atividade[v_incricao[indice].ID_atividade_inscricao].tipo_atividade == 2)
                    atividade2=atividade2+v_incricao[indice].valor_pago;
                if(v_atividade[v_incricao[indice].ID_atividade_inscricao].tipo_atividade == 3)
                    atividade3=atividade3+v_incricao[indice].valor_pago;
                if(v_atividade[v_incricao[indice].ID_atividade_inscricao].tipo_atividade == 4)
                    atividade4=atividade4+v_incricao[indice].valor_pago;
                if(v_atividade[v_incricao[indice].ID_atividade_inscricao].tipo_atividade == 5)
                    atividade5=atividade5+v_incricao[indice].valor_pago;
                if(v_atividade[v_incricao[indice].ID_atividade_inscricao].tipo_atividade == 6)
                    atividade6=atividade6+v_incricao[indice].valor_pago;
                soma_atividades=soma_atividades+atividade1+atividade2+atividade3+atividade4+atividade5+atividade6;
            }
    }
        printf("\n1-Académica:%2.f\n2-Lazer:%2.f\n3-Cultura:%2.f\n4-Desporto:%2.f\n5-Formação:%2.f\n6-Outra:%2.f\nTotal:%2.f\n",atividade1,atividade2,atividade3,atividade4,atividade5,atividade6,soma_atividades);
}
//grava no ficheiro os participantes
void gravar_ficheiro_participantes(t_participantes v_participante[], int numero_participantes)
{
    FILE *ficheiro_participantes;
    ficheiro_participantes = fopen("participantes.dat","wb");

    if (ficheiro_participantes == NULL)
        printf("\nNao foi possivel criar o ficheiro!");
    else
    {
        fwrite(&numero_participantes, sizeof(int), 1, ficheiro_participantes);
        fwrite(v_participante, sizeof(t_participantes), numero_participantes, ficheiro_participantes);
        fclose(ficheiro_participantes);
        printf("\nEscrita dos dados de %d participantes em ficheiro com sucesso.",numero_participantes);
    }
}
//grava no ficheiro as atividades
void gravar_ficheiro_atividades(t_atividade v_atividade[], int numero_atividades)
{
    FILE *ficheiro_atividades;
    ficheiro_atividades = fopen("atividades.dat","wb");

    if (ficheiro_atividades == NULL)
        printf("\nNao foi possivel criar o ficheiro!");
    else
    {
        fwrite(&numero_atividades, sizeof(int), 1, ficheiro_atividades);
        fwrite(v_atividade, sizeof(t_atividade), numero_atividades, ficheiro_atividades);
        fclose(ficheiro_atividades);
        printf("\nEscrita dos dados de %d atividades em ficheiro com sucesso.",numero_atividades);
    }
}


//grava no ficheiro as incrições
void gravar_ficheiro_inscricoes(t_inscricao v_inscricoes[], int numero_inscricoes)
{
    FILE *ficheiro_inscricoes;
    ficheiro_inscricoes = fopen("inscricoes.dat","wb");

    if (ficheiro_inscricoes == NULL)
        printf("\nNao foi possivel criar o ficheiro!");
    else
    {
        fwrite(&numero_inscricoes, sizeof(int), 1, ficheiro_inscricoes);
        fwrite(v_inscricoes, sizeof(t_inscricao), numero_inscricoes, ficheiro_inscricoes);
        fclose(ficheiro_inscricoes);
        printf("\nEscrita dos dados de %d inscricoes em ficheiro com sucesso.",numero_inscricoes);
    }
}

//dá "upload" aos ficheiros dos participantes ja  registados para a aplicação
int ler_ficheiro_participantes (t_participantes v_participante[])
{
    int numero_participantes, numero_participantes_lido ;
    FILE *ficheiro_participantes;
    ficheiro_participantes = fopen("participantes.dat","rb");

    if (ficheiro_participantes == NULL )
        printf("\nNao foi possivel abrir o ficheiro dos paticipantes!!");
    else
    {
        fread(&numero_participantes, sizeof(int), 1, ficheiro_participantes);
        numero_participantes_lido = fread(v_participante, sizeof(t_participantes),numero_participantes, ficheiro_participantes);
        fclose(ficheiro_participantes);

        if (numero_participantes_lido != numero_participantes)
        {
            numero_participantes = 0;


            printf("\nErro na leitura de dados do ficheiro dos participantes!");
        }
        else
            printf("\nLeitura dos dados de %d participantes de ficheiro com sucesso.", numero_participantes);
    }
    return numero_participantes;
}
//dá "upload" aos ficheiros das atividades ja  registadas para a aplicação
int ler_ficheiro_atividades (t_atividade v_atividade[])
{
    int numero_atividades, numero_atividades_lido ;
    FILE *ficheiro_atividades;

    ficheiro_atividades = fopen("atividades.dat","rb");

    if (ficheiro_atividades == NULL )
        printf("\nNao foi possivel abrir o ficheiro das atividades!!");
    else
    {
        fread(&numero_atividades, sizeof(int), 1, ficheiro_atividades);
        numero_atividades_lido = fread(v_atividade, sizeof(t_atividade),numero_atividades, ficheiro_atividades);
        fclose(ficheiro_atividades);

        if (numero_atividades_lido != numero_atividades)
        {
            numero_atividades = 0;


            printf("\nErro na leitura de dados do ficheiro das atividades!");
        }
        else
            printf("\nLeitura dos dados de %d Atividades de ficheiro com sucesso.", numero_atividades);

    }
    return numero_atividades;
}

//dá "upload" aos ficheiros das inscrições ja  registadas para a aplicação
int ler_ficheiro_inscricoes (t_inscricao v_inscricao[])
{
    int numero_inscricoes, numero_inscricoes_lido ;
    FILE *ficheiro_inscricoes;

    ficheiro_inscricoes = fopen("inscricoes.dat","rb");

    if (ficheiro_inscricoes == NULL )
        printf("\nNao foi possivel abrir o ficheiro das incrições!!");
    else
    {
        fread(&numero_inscricoes, sizeof(int), 1, ficheiro_inscricoes);
        numero_inscricoes_lido = fread(v_inscricao, sizeof(t_inscricao),numero_inscricoes, ficheiro_inscricoes);
        fclose(ficheiro_inscricoes);

        if (numero_inscricoes_lido != numero_inscricoes)
        {
            numero_inscricoes = 0;


            printf("\nErro na leitura de dados do ficheiro de incrições!");
        }
        else
            printf("\nLeitura dos dados de %d incrições de ficheiro com sucesso.", numero_inscricoes);

    }
    return numero_inscricoes;
}
//procura se o NIF esta repetido
int procura_NIF(t_participantes v_participante[], int tamanho,int min, int max)
{
    int indice=0,encontrou_valor = -1,valor;
    do
    {
        encontrou_valor=-1;
        valor = ler_numero("\nInsira o NIF do participante:",min,max);
        for(indice = 0; indice < tamanho; indice++)
        {
            if(v_participante[indice].NIF == valor)
                encontrou_valor = indice;

        }
        if (encontrou_valor != -1)
        {
            system("cls");
            printf("\nERRO: numero já existe!\n");
            printf("\nNumeros validos de %d a %d",min,max);
        }
        else
            v_participante[tamanho].NIF=valor;
    }
    while(encontrou_valor!=-1);
}
//procura se o contacto esta repetido
int procura_contacto(t_participantes v_participante[], int tamanho,int min, int max)
{
    int indice=0,encontrou_valor = -1,valor;
    do
    {
        encontrou_valor=-1;
        valor = ler_numero("\nInsira o contacto do participante:",min,max);
        for(indice = 0; indice < tamanho; indice++)
        {
            if(v_participante[indice].contacto == valor)
                encontrou_valor = indice;

        }
        if (encontrou_valor != -1)
        {
            system("cls");
            printf("\nERRO: numero já existe!\n");
            printf("\nNumeros validos de %d a %d",min,max);
        }
        else
            v_participante[tamanho].contacto=valor;
    }
    while(encontrou_valor!=-1);
    return valor;
}
//procura se o ID do participante exite
int procura_ID_participante(t_participantes v_participante[], int tamanho,int min, int max)
{
    int indice=0,encontrou_valor = -1,valor;
    do
    {
        encontrou_valor=-1;
        valor = ler_numero ("\nInsira o ID de Participante: ",min,max);
        for(indice = 0; indice < tamanho; indice++)
        {
            if(v_participante[indice].ID_participante == valor)
                encontrou_valor = indice;

        }
        if (encontrou_valor == -1)
        {
            system("cls");
            printf("\nERRO: numero não existe!");
            printf("\nNumeros validos de %d a %d",min,max);
        }
        // else
        //   v_participante[tamanho].ID_participante=valor;
    }
    while(encontrou_valor==-1);
    return valor;
}
//procura se o ID da atividade existe
int procura_ID_atividade(t_atividade v_atividade[], int tamanho,int min, int max)
{
    int indice=0,encontrou_valor = -1,valor;
    do
    {
        encontrou_valor=-1;
        valor = ler_numero ("\nInsira o ID da Atividade: ",min,max);
        for(indice = 0; indice < tamanho; indice++)
        {
            if(v_atividade[indice].ID_atividade == valor)
                encontrou_valor = indice;

        }
        if (encontrou_valor == -1)
        {
            system("cls");
            printf("\nERRO: numero não existe!");
            printf("\nNumeros validos de %d a %d",min,max);
        }
        //  else
        //    v_atividade[tamanho].ID_atividade=valor;
    }
    while(encontrou_valor==-1);
    return valor;
}
//verifica se a incrição é duplicada
int registo_duplicado(t_inscricao v_inscricao[], int tamanho,int id_participante, int id_atividade)
{
    int indice=0,encontrou_valor = -1,valor_paticipante,valor_atividade;

    for(indice = 0; indice < tamanho; indice++)
    {
        if(v_inscricao[indice].ID_participante_inscricao == valor_paticipante && v_inscricao[indice].ID_atividade_inscricao == valor_atividade)
            encontrou_valor = indice;

    }
    return encontrou_valor;
}

//regista no vetor data e hora atual
void data_hora_atual(t_data_hora *data_hora)
{
    time_t current_time = time(NULL);
    struct tm *local_time = localtime(&current_time);
    data_hora->dia = local_time->tm_mday;
    data_hora->mes = local_time->tm_mon + 1;
    data_hora->ano = local_time->tm_year + 1900;
    data_hora->hora = local_time->tm_hour;
    data_hora->minuto = local_time->tm_min;
    data_hora->segundo = local_time->tm_sec;
}
//lê um numero
int ler_numero(char *texto,int min, int max)
{
    int num;
    do
    {
        printf("%s",texto);
        fflush(stdin);
        scanf("%d", &num);
        if(num<min || num>max)
        {
            system("cls");
            printf("ERRO:numero invalido\nInsira um numero entre %d e %d:",min,max);
            getchar();
        }
    }
    while(num<min || num>max);
    return num;
}
//Le preço
float ler_preco(char *texto,int min, int max)
{
    float preco;
    do
    {
        printf("%s",texto);
        fflush(stdin);
        scanf("%f", &preco);
        if(preco<min || preco>max)
        {
            system("cls");
            printf("ERRO:numero invalido\nInsira um numero entre %d e %d:",min,max);
            getchar();
        }
    }
    while(preco<min || preco>max);
    return preco;
}
//lê uma string
char ler_string(char *texto, char *dados, char char1, char char2)
{
    do
    {
        printf("%s", texto);
        fflush(stdin);
        scanf("%80[^\n]s", dados);
        if(strchr(dados, char1) == NULL || strchr(dados, char2) == NULL)
        {
            system("cls");
            printf("ERRO: Campo tem de conter %c%c\n", char1, char2);
            getchar();
        }
    }
    while(strchr(dados, char1) == NULL || strchr(dados, char2) == NULL);
    return dados;
}
//menu de opções
int menu_opcoes()
{
    int opcao;
    do
    {
        printf("1-Registar Participante\n");
        printf("2-Consultar Participante\n");
        printf("3-Registar Atividade\n");
        printf("4-Consultar Atividade\n");
        printf("5-Resistar Inscrição\n");
        printf("6-Consultar Inscrição\n");
        printf("7-Estatisticas\n");
        printf("8-Gravar/Ler Ficheiros;\n");
        printf("0-Sair\n");
        printf("Opcção:");
        scanf("%d",&opcao);
        if (opcao<0 ||opcao>8)
        {
            system("cls");
            printf("\nERRO:Opção invalida\n");
            getchar();
        }
    }
    while(opcao<0 ||opcao>8);
    return opcao;
}
//sub menu para ficheiros
int menu_ficheiros()
{
    int opcao_ficheiro;
    do
    {
        printf("1-Ler Ficheiros(Participantes,Atividades,Registos)\n");
        printf("2-Gravar Ficheiros(Participantes,Atividades,Registos)\n");
        printf("0-Voltar atras\n");
        printf("Opcção:");
        scanf("%d",&opcao_ficheiro);
        if (opcao_ficheiro<1 ||opcao_ficheiro>2)
        {
            system("cls");
            printf("\nERRO:Opção invalida\n");
            getchar();
        }
    }
    while(opcao_ficheiro<0 ||opcao_ficheiro>2);
    return opcao_ficheiro;
}
//confirma a saida do utilizador
char confirma_saida()
{
    char confirma;
    do
    {
        system("cls");
        printf("\nDeseja mesmo sair");
        printf("\nS-sim     N-não\n");
        printf("Opcção:");
        scanf(" %c", &confirma);
        confirma=toupper(confirma);
        if(confirma!='S' && confirma!='N')
        {
            system("cls");
            printf("\nERRO:Opção invalida\n");
            getchar();
        }
    }
    while(confirma!='S' && confirma!='N');
    system("cls");
    return confirma;
}
