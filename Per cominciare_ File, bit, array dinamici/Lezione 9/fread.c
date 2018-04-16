
// esempi di uso delle funzioni fread e fwrite 
// frammento non funzionante! Serve solo a mostrare l'uso di fread/fwrite

int main()
{
  // il file deve essere aperto in lettura (per fread) o scrittura (per fwrite) 
  FILE *f;
  // scrittura singolo int
  int n=5;
  if(fwrite(&n, sizeof(int), 1, f)!=1) die("errore scrittura");
  //scrittura array coppie
  coppia a[n];
  if(fwrite(a,size(coppia),n,f)!=n) die("errore scrittura");
  // scrittra dello stesso array un elemento alla volta
  for(int i=0;i<n;i++)
    // voglio scrivere a[i] 
    if(fwrite(a+i,sizeof(coppia),1,f)!=1) die("errore scrittura");
    // Nota: a+i e' equivalente a &a[i]
    
  // lettura di un singolo int 
  if(fread(&n,sizeof(int),1,f)!=1)  die("errore lettura");   
  // lettura din un intero array di n coppie
  if(fread(a,sizeof(coppia),n,f)!=n)  die("errore lettura");   

}





