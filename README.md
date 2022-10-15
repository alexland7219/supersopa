# Supersopa
Projecte d'Algorísmia (FIB UPC) "Supersopa"

L'informe final d'aquest projecte el podeu trobar en format PDF o ODT en aquest mateix directori, que explica els fitxers i diferents implementacions en detall.

Si voleu executar el projecte, en un sistema GNU/Linux, cal fer:

```
make -j$(nproc)
./programa.x < EFFrandom.txt
``` 


On `EFFrandom.txt` és el diccionari que es vol processar. Es pot editar el fitxer `main.cc` per a canviar la mida del tauler i el nombre de paraules a amagar. Per defecte la mida és de 30x30 i s'hi amaguen 20 paraules.

Després es poden comprovar visualment si hi ha diferències dels fitxers output amb Meld (màxim tres a la vegada) (https://meldmerge.org)

`meld vector.out ternary.out bloom.out`

Tambés es pot fer amb `diff`. Finalment per a generar els histogrames cal descomentar parts del codi dels filtres de Bloom (està explicat en detall al informe), i després d'executar el programa, fer:

`python3 histogram.py`
