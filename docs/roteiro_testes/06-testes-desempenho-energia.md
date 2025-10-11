# 6. Testes de Desempenho e Energia

| Código | Nome do Teste             | Tipo      | Objetivo                                 | Pré-condições | Procedimento                                                                                                                                                                                                                                                                                                                              | Resultado Esperado | Requisito Relacionado |
| ------ | ------------------------- | --------- | ---------------------------------------- | ------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------------------ | --------------------- |
|        | Duração da bateria        | Sistema   | Verificar autonomia mínima.              |               | 1\. Criar uma missão padrão que dure aproximadamente 5 minutos.<br>2\. Iniciar a execução da missão em loop contínuo.<br>3\. Monitorar o tempo com um cronômetro.<br>4\. Registrar o tempo total de operação até que o carrinho pare por falta de energia ou o sistema de monitoramento de bateria indique nível crítico.                 |                    |                       |
|        | Precisão da trajetória    | Funcional | Avaliar erro entre caminho ideal e real. |               | 1\. Marcar uma trajetória no chão com fita adesiva (ex: um quadrado de 1m x 1m).<br>2\. Enviar os comandos para o carrinho percorrer exatamente essa trajetória.<br>3\. Ao final da missão, medir a distância entre o ponto final real do carrinho e o ponto final esperado.<br>4\. Comparar os dados do relatório com o percurso físico. |                    |                       |
|        | Consumo de corrente total | Unitário  | Confirmar corrente total de 1.3 A aprox. |               | 1\. Conectar um multímetro em modo amperímetro, em série com a alimentação principal do carrinho.<br>2\. Ligar o carrinho e todos os seus sistemas.<br>3\. Enviar um comando que exija esforço máximo (ex: avançar com a carga máxima de 1kg).<br>4\. Registrar o pico de corrente medido no multímetro.                                  |                    |                       |






### Histórico de Versões

| Versão | Data       | Descrição                                      | Autor               | Revisor            |
|--------|------------|------------------------------------------------|---------------------|--------------------|
| 1.0    | 11/10/2025 | Criação do documento | [João Pedro](https://github.com/JoaoPedrooSS)          |  [João Lucas](https://github.com/jlucasiqueira)  |
| 1.1    | 11/10/2025 | Estruturação de métodos para medir a autonomia da bateria e a precisão da trajetória. | [Johan Rocha](https://github.com/johan-rocha)          |  [João Lucas](https://github.com/jlucasiqueira)  |