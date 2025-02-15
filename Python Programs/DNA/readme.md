Command Line Input: python3 csv_database/large.csv sequences/10.txt

En genética molecular, los microsatélites (SSR o STR por sus acrónimos en inglés para simple sequence repeat y short tandem repeat) son secuencias de ADN en las que un fragmento (cuyo tamaño va desde dos hasta seis pares de bases) se repite de manera consecutiva. La variación en el número de repeticiones, y no la secuencia repetida, crea diferentes alelos. (WIKIPEDIA)

Este programa recibe una base de datos en un archivo .csv con los siguientes campos: name,AGATC,TTTTTTCT,AATG,TCTAG,GATA,TATC,GAAA,TCTG
y una secuencia capturada de una escena, en formato .txt. Primero se obtiene las repeticiones máximas de AGTC, ..., TCTG y se compara con cada persona que esté en la base y luego se determina un sospechoso.

Si escribimos en la termina python3 csv_database/large.csv sequences/10.txt, tendremos como sospechoso a Albus, ya que tiene una coincidencia del 100%
