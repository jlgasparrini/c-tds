class test_comentarios{
/*  Este es un programa donde estamos probando los comentarios /* asi q pueden aparecer simbolos raros y es solo a modo de prueba % ldk$ &

 /*  sigo probando @ [ ^ * - 784 { } //   *   / y asi podria seguir.... 

" $ ¬ °  ! ¡ ? ~ & % · #  */
int pruAritmetica(int b, int c ){
	
        float res;// tambien puede haber comentarios de una linea

	if(b > c){ /* este es otro comentario */ 
		res = b + 5;
        }
	else{
		res = c;
        }
	return res;
		
	}

int main(){ // dentro de este comentario podria aparecer /* o */ y no deberia haber drama. " $ ¬ ° | ! ¡ ? ~ & % · # 
    externinvk("printf", int , pruAritmetica(4,8 ));
}

}
