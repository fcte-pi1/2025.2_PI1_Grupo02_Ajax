# Política de Branches e Commits do Projeto (Trunk-Based Development)

Este documento descreve o fluxo de trabalho com Git, o modelo de branches e o padrão para mensagens de commit a serem seguidos por todos os contribuidores do projeto. A adesão a estas regras é fundamental para manter o repositório organizado, o histórico de alterações legível e permitir a entrega contínua de valor.

## 1. Política de Branches: Trunk-Based Development

Adotamos o modelo de **Trunk-Based Development (TBD)**, que foca em manter uma única branch principal (`main`) sempre em estado estável e pronta para ser lançada. O desenvolvimento é feito em branches de vida curta que são integradas rapidamente ao tronco.

**Fluxo Geral:** `feature` -> `main`

### A Branch Principal (O Tronco)

Esta é a única branch de longa duração do repositório.

#### `main`
- **Propósito:** É a única fonte de verdade do projeto. Armazena o histórico completo e linear do desenvolvimento e **DEVE** estar sempre em um estado passível de ser implantado em produção.
- **Regras:**
  - **NUNCA** se deve enviar commits diretamente para a `main`. Todo o código deve ser integrado via Pull Requests (PRs).
  - Todo merge na `main` deve passar por revisões de código e por uma suíte de testes automatizados (CI - Continuous Integration).
  - Lançamentos (releases) são feitos a partir de commits específicos da `main`, que são marcados com uma tag de versão (ex: `v1.0.0`, `v1.1.0`).

### Branches de Curta Duração

Estas branches são temporárias e devem ser removidas imediatamente após o merge. Elas devem ter um ciclo de vida muito curto, idealmente de poucas horas a no máximo um dia.

#### `feature/*` ou `fix/*`
- **Propósito:** Desenvolver uma nova funcionalidade, corrigir um bug ou realizar qualquer outra tarefa. O objetivo é que a alteração seja pequena e focada.
- **Nomenclatura:**
  - `feature/nome-da-funcionalidade-em-kebab-case`
  - `fix/descricao-da-correcao-em-kebab-case`
- **Fluxo:**
  1. São sempre criadas a partir do estado mais recente da `main`.
  2. Ao serem concluídas, um Pull Request (PR) é aberto para fazer o merge de volta para a `main`.
  3. Elas devem ser atualizadas com frequência a partir da `main` para evitar conflitos grandes no momento do merge.

### Como Lidar com Releases e Hotfixes?

- **Releases:** Não existem branches `release/*`. Uma nova versão é simplesmente uma "foto" (um commit) da `main` em um determinado momento. O processo de lançamento é automatizado: quando um commit na `main` é considerado pronto para ser uma nova versão, uma tag Git é criada a partir dele (ex: `git tag v1.2.0`), o que dispara o processo de deploy (CD - Continuous Deployment).

- **Hotfixes:** Não existem branches `hotfix/*`. Uma correção crítica em produção é tratada como qualquer outra tarefa: cria-se uma branch a partir da `main` (`fix/corrige-bug-critico`), a correção é implementada, testada e integrada de volta à `main` via PR. Por ser uma prioridade, esse processo acontece de forma acelerada.

> **Nota sobre Feature Flags:** Para permitir a integração contínua de funcionalidades que ainda não estão prontas para o usuário final, utilizamos **Feature Flags** (ou "toggles"). Isso permite que o código seja integrado à `main` sem estar ativo em produção, desacoplando o deploy da funcionalidade do seu lançamento.

---

## 2. Política de Commits: Conventional Commits

Para manter um histórico claro e automatizável, todas as mensagens de commit devem seguir o padrão [Conventional Commits](https://www.conventionalcommits.org/).

**Estrutura:** `tipo(escopo): descrição`

### Tipos (`tipo`)

O tipo deve ser um dos seguintes:

- **feat**: Para uma nova funcionalidade.
- **fix**: Para a correção de um bug.
- **docs**: Para alterações exclusivas na documentação.
- **style**: Para alterações de formatação que não afetam o código (espaços, ponto e vírgula, etc.).
- **refactor**: Para uma alteração de código que não corrige um bug nem adiciona uma funcionalidade.
- **test**: Para adicionar ou corrigir testes.
- **build**: Para alterações que afetam o sistema de build ou dependências externas.
- **ci**: Para alterações em arquivos e scripts de CI/CD.

### Escopos (`escopo`)

O escopo identifica a área do projeto que foi alterada. Os escopos principais do nosso projeto são:

- `software`: Relacionado a qualquer código embarcado, algoritmos, APIs, etc.
- `hardware`: Relacionado a esquemáticos, design de PCBs, seleção de componentes.
- `energia`: Relacionado ao sistema de gerenciamento de baterias, consumo, etc.
- `estruturas`: Relacionado ao chassi, design mecânico, materiais e montagem.

*É possível usar sub-escopos para maior detalhe, como `software-navegacao` ou `hardware-sensores`.*

### Descrição (`descrição`)

- Escrita em modo imperativo (ex: "adiciona", "corrige", "altera").
- Começa com letra minúscula.
- Não termina com ponto final.

### Exemplos Práticos
```sh
feat(software): implementa módulo de reconhecimento de Aruco markers
fix(hardware): ajusta pinagem do microcontrolador para o novo IMU
docs(energia): detalha o diagrama do circuito de carregamento
refactor(software-navegacao): otimiza o algoritmo de planejamento de rota
feat(estruturas): projeta novo chassi em SolidWorks para redução de peso
```

## 3. Fluxo de Trabalho Prático (Passo a Passo)

1.  **Sincronize com `main`**:
```sh
git checkout main
git pull origin main
```
2.  **Crie sua branch de trabalho**:
```sh
git checkout -b feature/minha-nova-funcionalidade
```
3.  **Trabalhe e Faça Commits**:
    - Faça suas alterações (mantenha-as pequenas e focadas).
    - Adicione os arquivos (`git add .`).
    - Crie um commit seguindo o padrão (`git commit -m "feat(software): minha nova feature"`).
    - **Importante:** Sincronize sua branch com a `main` frequentemente para evitar conflitos complexos no futuro.
```bash
git pull --rebase origin main
```
4.  **Envie sua Branch**:
```sh
git push origin feature/minha-nova-funcionalidade
```
5.  **Abra um Pull Request (PR)**:
    - No GitHub (ou outra plataforma), abra um PR da sua branch para a branch `main`.
    - Descreva as alterações e marque os revisores necessários. Garanta que os testes automatizados passaram.
6.  **Revisão e Merge**:
    - Participe da discussão no PR e faça os ajustes solicitados.
    - Após a aprovação e a passagem da CI, o PR será "merged" (usando "squash and merge", se preferível) na `main`. Sua branch será deletada em seguida.

A consistência de todos em seguir este guia é o que garantirá um ciclo de desenvolvimento rápido, seguro e escalável.


### Histórico de Versões

| Versão | Data       | Descrição                                      | Autor               | Revisor            |
|--------|------------|------------------------------------------------|---------------------|--------------------|
| 1.0    | 11/10/2025 | Criação do documento | [Johan Rocha](https://github.com/johan-rocha)          |  [Francisco](https://github.com/francisco1penha)  |
