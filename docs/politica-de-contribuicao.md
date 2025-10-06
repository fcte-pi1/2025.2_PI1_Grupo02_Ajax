# Política de Branches e Commits do Projeto

Este documento descreve o fluxo de trabalho com Git, o modelo de branches e o padrão para mensagens de commit a serem seguidos por todos os contribuidores do projeto. A adesão a estas regras é fundamental para manter o repositório organizado, o histórico de alterações legível e o processo de lançamento de novas versões eficiente.

## 1. Política de Branches: GitFlow Adaptado

Utilizamos o modelo GitFlow, que organiza o trabalho em torno de lançamentos de versões. Ele é composto por branches de longa duração e branches de curta duração.

**Fluxo Geral:** `feature` -> `develop` -> `release` -> `main`

### Branches de Longa Duração

Estas branches permanecem no repositório indefinidamente.

#### `main`
- **Propósito:** Armazena o código de todas as versões oficiais e estáveis. Esta branch é o espelho do que está em "produção".
- **Regras:**
  - **NUNCA** se deve enviar commits diretamente para a `main`.
  - Ela só recebe merges de branches `release/*` ou `hotfix/*`.
  - Cada merge na `main` **DEVE** ser acompanhado de uma tag Git que identifica a versão (ex: `v1.0.0`, `v1.1.0`).

#### `develop`
- **Propósito:** É a branch principal de desenvolvimento. Ela contém o código mais recente, incluindo todas as funcionalidades que serão incluídas no próximo lançamento.
- **Regras:**
  - É a branch de partida para a criação de novas `feature/*`.
  - Recebe merges de `feature/*` concluídas e revisadas.
  - Representa o estado "pré-lançamento" do projeto.

### Branches de Curta Duração

Estas branches são temporárias e devem ser removidas após o merge.

#### `feature/*`
- **Propósito:** Desenvolver uma nova funcionalidade específica.
- **Nomenclatura:** `feature/nome-da-funcionalidade-em-kebab-case`
- **Fluxo:**
  1. Criada a partir de `develop`.
  2. Ao ser concluída, um Pull Request (PR) é aberto para fazer o merge de volta para `develop`.

#### `release/*`
- **Propósito:** Preparar o lançamento de uma nova versão. Nesta fase, apenas correções de bugs e ajustes finais são permitidos.
- **Nomenclatura:** `release/vX.Y.Z` (ex: `release/v1.2.0`)
- **Fluxo:**
  1. Criada a partir de `develop`.
  2. Após estabilizada, é feito o merge para `main` (com tag) e também para `develop` (para incorporar as correções de última hora).

#### `hotfix/*`
- **Propósito:** Corrigir um bug crítico na versão estável (`main`).
- **Nomenclatura:** `hotfix/descricao-da-correcao`
- **Fluxo:**
  1. Criada a partir de `main`.
  2. Após a correção, é feito o merge para `main` (com nova tag, ex: `v1.1.1`) e também para `develop`.

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

- **`software`**: Relacionado a qualquer código embarcado, algoritmos, APIs, etc.
- **`hardware`**: Relacionado a esquemáticos, design de PCBs, seleção de componentes.
- **`energia`**: Relacionado ao sistema de gerenciamento de baterias, consumo, etc.
- **`estruturas`**: Relacionado ao chassi, design mecânico, materiais e montagem.

*É possível usar sub-escopos para maior detalhe, como `software-navegacao` ou `hardware-sensores`.*

### Descrição (`descrição`)

- Escrita em modo imperativo (ex: "adiciona", "corrige", "altera" em vez de "adicionado", "corrigindo").
- Começa com letra minúscula.
- Não termina com ponto final.

### Exemplos Práticos

```
feat(software): implementa módulo de reconhecimento de Aruco markers
fix(hardware): ajusta pinagem do microcontrolador para o novo IMU
docs(energia): detalha o diagrama do circuito de carregamento
refactor(software-navegacao): otimiza o algoritmo de planejamento de rota
feat(estruturas): projeta novo chassi em SolidWorks para redução de peso
```

---

## 3. Fluxo de Trabalho Prático (Passo a Passo)

1. **Sincronize com `develop`**:
   ```bash
   git checkout develop
   git pull origin develop
   ```
2. **Crie sua branch de feature**:
   ```bash
   git checkout -b feature/minha-nova-funcionalidade
   ```
3. **Trabalhe e Faça Commits**:
   - Faça suas alterações.
   - Adicione os arquivos (`git add .`).
   - Crie um commit seguindo o padrão (`git commit -m "feat(software): minha nova feature"`).
4. **Envie sua Branch**:
   ```bash
   git push origin feature/minha-nova-funcionalidade
   ```
5. **Abra um Pull Request (PR)**:
   - No GitHub, abra um PR da sua branch para a branch `develop`.
   - Descreva as alterações e marque os revisores necessários.
6. **Revisão e Merge**:
   - Participe da discussão no PR e faça os ajustes solicitados.
   - Após a aprovação, o PR será "merged" por um mantenedor do projeto.

A consistência de todos em seguir este guia é o que garantirá o sucesso e a escalabilidade do nosso trabalho em equipe.
