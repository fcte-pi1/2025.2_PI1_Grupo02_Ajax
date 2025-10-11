# 7. Testes de Interface e Usabilidade

| Código | Nome do Teste                    | Tipo      | Objetivo                                     | Pré-condições | Procedimento                                                                                                                                                                                                                                                                                         | Resultado Esperado | Requisito Relacionado |
| ------ | -------------------------------- | --------- | -------------------------------------------- | ------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------------------ | --------------------- |
|        | Acesso e login (se aplicável)    | Funcional | Verificar autenticação na interface.         |               | 1\. Acessar a URL da interface.<br>2\. Inserir um usuário e senha inválidos e clicar em 'Entrar'. Verificar se uma mensagem de erro é exibida.<br>3\. Inserir credenciais válidas e clicar em 'Entrar'.                                                                                              |                    |                       |
|        | Envio de comandos via painel     | Funcional | Garantir que botões e campos funcionam.      |               | 1\. Navegar para a tela de criação de missão.<br>2\. Utilizar os campos de texto ou botões para adicionar 3 comandos diferentes à sequência.<br>3\. Clicar no botão 'Enviar Missão'.<br>4\. Verificar se a interface exibe uma confirmação de envio e se o backend registra o recebimento da missão. |                    |                       |
|        | Exibição de relatório e gráficos | Funcional | Validar renderização de dados de trajetória. |               | 1\. Navegar para a seção de 'Histórico' ou 'Relatórios' da interface.<br>2\. Clicar em uma missão finalizada da lista.<br>3\. Observar a tela de detalhes.<br>4\. Verificar se o gráfico com a trajetória planejada vs. a real é exibido e se os dados correspondem ao que foi executado.            |                    |                       |








### Histórico de Versões

| Versão | Data       | Descrição                                      | Autor               | Revisor            |
|--------|------------|------------------------------------------------|---------------------|--------------------|
| 1.0    | 11/10/2025 | Criação do documento | [João Pedro](https://github.com/JoaoPedrooSS)          |  [João Lucas](https://github.com/jlucasiqueira)  |
| 1.1    | 11/10/2025 | Desenvolvimento dos procedimentos para simulação de uma missão completa ponta a ponta. | [Johan Rocha](https://github.com/johan-rocha)          |  [João Lucas](https://github.com/jlucasiqueira)  |