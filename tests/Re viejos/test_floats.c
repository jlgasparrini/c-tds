class test_flotantes{

float div(float a, float b){
   return a / b;
}

float resta(float a, float b){
  return a - b;
}

float sum(float a, float b){
  return a + b;
}
void main(){

    float x, y, z;
    
    x= 6.982;
    y= -2.5;     // modificamos el numero -002.5 por -2.5 ya que no permitimos 0 no significativos
    z= 3.5698;
    
    externinvk("printf", float , "anidandofuncionesflotantes", sum(res(y,x), div(x,z)) );
}

}
