/************************************************************************************************
*Define la estructura y funciones asociadas para un Nodo a ser utilizado en listas encadenadas  *
*Un nodo esta formado por :                                                                     *
*- info         :   la informacion contenida por el nodo                                        *
*- next		    :   un puntero al siguiente nodo                                                *
*************************************************************************************************/

#ifndef LINKNODEOFFSET_H
#define LINKNODEOFFSET_H

typedef struct NodeStackOffset {
    int *info;
    struct NodeStackOffset *next;
} NodeStackOffset;

/*funciones publicas para manipular nodos*/

/*constructores*/

NodeStackOffset* newLinkNodeOffset_empty();
NodeStackOffset* newLinkNodeOffset_info(int);
NodeStackOffset* newLinkNodeOffset_info_next(int, NodeStackOffset*);

/*lectura de informacion*/

int getInfo_linkNodeOffset(NodeStackOffset*);
NodeStackOffset* getNext_linkNodeOffset(NodeStackOffset*);

/*escritura de informacion*/
void setInfo_linkNodeOffset(NodeStackOffset*, int);
void setNext_linkNodeOffset(NodeStackOffset*, NodeStackOffset*);

#endif
