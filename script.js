const quizData = {
    savings: [
      {
        question: "What is the recommended percentage of income to save each month?",
        options: ["10%", "20%", "30%", "50%"],
        answer: "20%"
      },
      {
        question: "What is the purpose of an emergency fund?",
        options: ["To invest in stocks", "To pay for unexpected expenses", "To buy luxury items", "To fund vacations"],
        answer: "To pay for unexpected expenses"
      },
      {
        question: "What is a common type of savings account?",
        options: ["Checking account", "IRA", "401(k)", "High-yield savings account"],
        answer: "High-yield savings account"
      }
    ],
    budgeting: [
      {
        question: "What is the first step in creating a budget?",
        options: ["Track your expenses", "Set financial goals", "Create a budget spreadsheet", "Identify your income sources"],
        answer: "Identify your income sources"
      },
      {
        question: "What is the purpose of tracking expenses?",
        options: ["To overspend", "To analyze spending habits", "To hide financial information", "To ignore financial planning"],
        answer: "To analyze spending habits"
      },
      {
        question: "What is a common budgeting technique?",
        options: ["Pay yourself first", "Spend everything you earn", "Never save money", "Ignore budgeting altogether"],
        answer: "Pay yourself first"
      }
    ],
    investing: [
      {
        question: "What is an example of a long-term investment?",
        options: ["Savings account", "Stocks", "Checking account", "CDs"],
        answer: "Stocks"
      },
      {
        question: "What is the primary goal of investing?",
        options: ["To lose money", "To gain financial independence", "To spend all savings", "To accumulate debt"],
        answer: "To gain financial independence"
      },
      {
        question: "What is a common type of investment account?",
        options: ["Savings account", "401(k)", "Checking account", "Credit card"],
        answer: "401(k)"
      }
    ]
  };
  
  function loadQuestions(topic) {
    const topicContainer = document.getElementById(topic);
    const questionsContainer = topicContainer.querySelector('.questions');
    const contentContainer = topicContainer.querySelector('.content');
    const content = {
      savings: "Savings is the process of setting aside a portion of income for future use, typically to meet short-term goals or to prepare for unexpected expenses.",
      budgeting: "Budgeting is the process of creating a plan to manage your income and expenses. It involves setting financial goals, tracking spending, and allocating resources.",
      investing: "Investing involves committing money to an asset or endeavor with the expectation of obtaining additional income or profit. It can help build wealth over time and achieve long-term financial goals."
    };
  
    contentContainer.textContent = content[topic];
  
    quizData[topic].forEach((q, index) => {
      const questionElement = document.createElement('div');
      questionElement.classList.add('question');
      questionElement.innerHTML = `
        <p>${index + 1}. ${q.question}</p>
        <form id="${topic}-form${index}">
          ${q.options.map((option, optionIndex) => `
            <label>
              <input type="radio" name="${topic}-answer${index}" value="${option}">
              ${option}
            </label>
          `).join('')}
        </form>
      `;
      questionsContainer.appendChild(questionElement);
    });
  }
  
  loadQuestions('savings');
  loadQuestions('budgeting');
  loadQuestions('investing');
  