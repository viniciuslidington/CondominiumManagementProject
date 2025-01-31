# Sistema de Gerenciamento de Condomínios

Este projeto é um sistema de gerenciamento de condomínios desenvolvido em C++. Ele permite que gestores e moradores interajam com diversas funcionalidades relacionadas à administração do condomínio.

## Funcionalidades Principais

### Para Gestores

- Gerenciar moradores e trabalhadores
  - Adicionar/Remover Moradores
  - Adicionar/Remover Trabalhadores
  - Ver feedbacks dos moradores
- Gerenciar ações do condomínio
  - Adicionar e visualizar avisos
  - Reservar áreas comuns
  - Registrar e visualizar serviços
  - Visualizar histórico de atividades
- Exibir informações gerais do condomínio

### Para Moradores

- Reservar áreas comuns
- Enviar feedbacks ou sugestões
- Visualizar regras do condomínio
- Ver lista de funcionários
- Acessar avisos
- Realizar pagamentos
- Exibir informações pessoais

## Estrutura do Código

O código é estruturado utilizando a programação orientada a objetos (POO) e conta com as seguintes classes principais:

- **Sistema**: Responsável por gerenciar o fluxo geral do sistema.
- **User (Classe Base)**: Classe genérica para usuários.
- **Manager (Herdeira de User)**: Representa o gestor do condomínio.
- **Resident (Herdeira de User)**: Representa um morador do condomínio.
- **ValidacaoInputs**: Responsável por validar entradas do usuário.

Além disso, os dados dos usuários são armazenados em arquivos JSON dentro da pasta `bdjson/usuarios.json`.

## Como Executar o Sistema

### Pré-requisitos

- Compilador C++ compatível com C++11 ou superior.
- Biblioteca [nlohmann/json](https://github.com/nlohmann/json) para manipulação de arquivos JSON.

### Compilação

Compile o projeto utilizando um compilador C++:

```sh
 g++ -o sistema main.cpp -std=c++11
```

### Execução

Após a compilação, execute o programa com:

```sh
 ./sistema
```

## Login

O sistema inicia solicitando o login do usuário. Caso seja um gestor ou morador válido, ele será redirecionado ao menu correspondente. Se as credenciais forem inválidas, o login será solicitado novamente.

## Estrutura de Pastas

```
/
├── main.cpp  # Código principal
├── classes/
│   ├── Manager.hpp
│   ├── Resident.hpp
│   ├── Sistema.hpp
│   ├── ValidacaoInputs.hpp
├── bdjson/
│   ├── usuarios.json  # Base de dados dos usuários
├── json.hpp  # Biblioteca para manipulação de JSON
└── README.md  # Este documento
```

## Melhorias Futuras

- Implementar interface gráfica para facilitar o uso.
- Adicionar autenticação mais segura (hash de senhas).
- Criar uma API para integração com outros sistemas.

## Contribuições

Sinta-se à vontade para contribuir com melhorias e novas funcionalidades! Basta abrir um pull request no repositório.

---

**Desenvolvido por Vinícius Lidington & Marcelo Melo**

