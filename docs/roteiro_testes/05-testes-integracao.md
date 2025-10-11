# 5. Testes de Integração

| Código | Nome do Teste                                       | Tipo          | Objetivo                                 | Pré-condições | Procedimento                                                                                                                                                                                                                                                                                                                                                                        | Resultado Esperado | Requisito Relacionado |
| ------ | --------------------------------------------------- | ------------- | ---------------------------------------- | ------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------------------ | --------------------- |
|        | Comunicação completa carrinho ↔ backend ↔ interface | Sistema       | Validar ciclo completo de uma missão.    |               | 1\. Acessar a interface web.<br>2\. Inserir uma rota (ex: "avançar 1m", "virar 90°", "avançar 0.5m").<br>3\. Clicar no botão para iniciar a missão.<br>4\. Observar o carrinho executando fisicamente a sequência de comandos.<br>5\. Após a conclusão, solicitar o relatório da missão pela interface.<br>6\. Verificar se os dados da trajetória real foram recebidos e exibidos. |                    |                       |
|        | Perda temporária de conexão                         | Não funcional | Avaliar comportamento em falha de Wi-Fi. |               | 1\. Iniciar uma missão.<br>2\. No meio da execução, desligar o roteador Wi-Fi por 10 segundos.<br>3\. Observar se o carrinho para ou se entra em modo de espera.<br>4\. Ligar novamente o roteador.<br>5\. Observar se o ESP32 se reconecta automaticamente ao servidor e continua a missão do ponto onde parou.                                                                    |                    |                       |





### Histórico de Versões

| Versão | Data       | Descrição                                      | Autor               | Revisor            |
|--------|------------|------------------------------------------------|---------------------|--------------------|
| 1.0    | 11/10/2025 | Criação do documento | [João Pedro](https://github.com/JoaoPedrooSS)          |  [João Lucas](https://github.com/jlucasiqueira)  |
| 1.1    | 11/10/2025 | Criação de cenários para validar o fluxo completo de dados e o comportamento em falhas. | [Johan Rocha](https://github.com/johan-rocha)          |  [João Lucas](https://github.com/jlucasiqueira)  |