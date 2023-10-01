# ar_condicionado
Projeto Arduino que monitora e coleta dados de temperatura e umidade do ambiente, e, baseado em limites pré-definidos de temperatura, controla automaticamente a ativação e desativação de um ar condicionado da Electrolux.

# Descrição:
- Este projeto utiliza um Arduino para monitorar a temperatura e a umidade do ambiente. Com base nos dados coletados, o sistema controla automaticamente um ar condicionado da Electrolux, ligando ou desligando-o conforme a necessidade, de acordo com os limites pré-definidos de temperatura. Além disso, é possível visualizar as informações no display LCD e, através dos comandos IR, o sistema pode ligar e desligar outros dispositivos, como a televisão e a Netflix.

# Componentes
- Arduino
- Sensor DHT11 (para medição de temperatura e umidade)
- Emissor de IR (para enviar comandos ao ar condicionado e outros dispositivos)
- Display LCD I2C

# Características Principais
- Monitoramento de Temperatura e Umidade: Com o sensor DHT11, o sistema monitora constantemente a temperatura e a umidade do ambiente.
- Controle Automático do Ar Condicionado: Baseado nos valores pré-definidos de temperatura, o ar condicionado é ligado ou desligado automaticamente para manter o ambiente confortável.
- Interface de Usuário: O display LCD mostra mensagens de boas-vindas e exibe as informações sobre a temperatura e a umidade, oferecendo feedback visual ao usuário.
- Controle de Dispositivos Adicionais: Com os comandos de IR, o sistema pode controlar outros dispositivos, como ligar a televisão ou acessar a Netflix.

# Código Principal
- O código começa com a inclusão das bibliotecas necessárias e a definição dos pinos. O sistema utiliza a biblioteca dht11 para interagir com o sensor de temperatura e umidade, IRremote para o controle por infravermelho e LiquidCrystal_I2C para o display LCD.

- Há variáveis definidas para armazenar as leituras de temperatura (t) e umidade (h). As variáveis desligar_ar e ligar_ar ajudam a controlar o estado do ar condicionado.

- No setup, o display é inicializado e apresenta mensagens de boas-vindas. Em seguida, no loop principal, o sistema verifica constantemente a temperatura e a umidade e toma decisões sobre ligar ou desligar o ar condicionado com base nesses valores.

# Conclusão
Esse projeto oferece uma solução prática e automatizada para manter o ambiente em uma temperatura agradável, economizando energia ao ligar o ar condicionado apenas quando necessário. A adição do display e do controle de dispositivos adicionais aumenta a utilidade e versatilidade do sistema.

# Long IR Signal Recorder com Arduino
Este projeto foi desenvolvido por AnalysIR e tem o propósito de contornar uma limitação comum em bibliotecas Arduino IR. Ele permite capturar timings brutos de sinais IR mais longos do que 255 marcas e espaços, tornando-se particularmente útil para sinais longos, como aqueles usados por condicionadores de ar.

1. Descrição Geral:
- Pino LED (13): Um indicador visual que mostra quando um sinal foi recebido.
- Buffer de Armazenamento: Um array irBuffer é usado para armazenar os timings. Ele tem uma capacidade máxima definida como maxLen, que é atualmente 800.
- Pino do Receptor IR (2): O sinal de saída do receptor IR é conectado ao pino 2, mas outros pinos também podem ser usados, dependendo do Arduino em questão.

2. Funcionamento:
- Início: Ao ligar, o Arduino se coloca em modo de espera e pede que o usuário pressione um botão do controle remoto.
- Recepção do Sinal: Quando o sinal IR é detectado, ele começa a armazenar as transições de sinal em irBuffer usando uma Interrupção de Serviço (ISR).
- Exibição: Após a captura, o programa irá exibir os timings no Serial Monitor em um formato cru.

3. Uso:
- Compile e carregue o código no seu Arduino.
- Abra o Serial Monitor com uma taxa de transmissão (BAUD rate) de 115200.
- Siga as instruções no Serial Monitor e pressione o botão do controle remoto.
- Veja os timings brutos exibidos.
  
- Dicas:
• Conexões:
• Receptor IR:
• V+ -> +5v
• GND -> GND
• Sinal de Saída -> Pino 2

• Se você estiver usando um Arduino 3V3, conecte o V+ ao +3V3.

4. Contribuições e Licença:
Este software foi escrito por AnalysIR. O uso é gratuito, sujeito às condições postadas no blog de AnalysIR. Ao usar este código, dê crédito ao AnalysIR e forneça um link para o blog deles, se possível. Mais detalhes sobre a licença podem ser encontrados no link fornecido no código.

# Sobre o Autor
- Desenvolvido por Rogério Moreira Alves Júnior.
- Possui expertise avançada em linguagens de programação, destacando-se em C, C++, Python e Java, e demonstra aptidão em análises numéricas com Octave e MatLab. No domínio do desenvolvimento web, tem proficiência em JavaScript, HTML e CSS. Em relação às ferramentas, apresenta domínio em Excel Avançado e VBA, evidenciando suas capacidades analíticas e de automação. Sua familiaridade com Arduino atesta competência em automação eletrônica, e sua destreza em AutoCAD e SOLIDWORKS sublinha habilidades em modelagem e design técnico na engenharia.

- Estudou Engenharia Mecânica na Universidade Federal de Santa Maria, Rio Grande do Sul, de 2019 a 2022 e atualmente é graduando em Engenharia Elétrica pela Universidade de Goiás, Goiânia, desde 2022. Destaca-se por sua experiência nas áreas de Engenharia Mecânica e Engenharia Elétrica, particularmente no desenvolvimento de programas computacionais e na elaboração de sistemas de automação com Arduino. Integrou o grupo de pesquisa Núcleo de Inovação e Competitividade (NIC) de 2021 a 2022, voltado para pesquisas em soluções de gestão empresarial, e participou de projetos focados no desenvolvimento de conteúdo técnico-gerencial através de modelos matemáticos para mensuração da competitividade da geração distribuída no Brasil. Além disso, colaborou no Projeto BAJA SAE pela UFSM, contribuindo para a construção e teste de um protótipo de veículo off-road em competições da SAE Brasil. Em 2023, fez parte da Equipe RoboCup Humanoid League no Núcleo de Robótica Pequi Mecânico da UFG, trabalhando no desenvolvimento de robôs humanoides autônomos e, sob sua atuação, a equipe conquistou o 1° e 2° lugares em duas categorias na Latin American Competition Of Robotics (LARC). Como desenvolvedor, assinou projetos relacionados à Engenharia Elétrica, como eficientização de iluminação e cálculo de fatura de energia para o Grupo B. Sua contribuição acadêmica se reflete em publicações em eventos como ICPR, SEPOC, CBENS e JAI-UFSM.
