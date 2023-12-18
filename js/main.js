const fac = (n) => (n > 1 ? n * fac(n - 1) : 1);

const top = 0;
const parent = (i) => ((i + 1) >>> 1) - 1;
const left = (i) => (i << 1) + 1;
const right = (i) => (i + 1) << 1;

const toHexChar = (num) => {
  if (num < 10) {
    return num;
  }

  switch(num) {
    case 10:
      return "A";
    case 11:
      return "B";
    case 12:
      return "C";
    case 13:
      return "D";
    case 14:
      return "E";
    case 15:
      return "F";
  }
}

class PriorityQueue {
  constructor(comparator = (a, b) => a > b) {
    this._heap = [];
    this._comparator = comparator;
  }
  size() {
    return this._heap.length;
  }
  isEmpty() {
    return this.size() == 0;
  }
  peek() {
    return this._heap[top];
  }
  push(...values) {
    values.forEach((value) => {
      this._heap.push(value);
      this._siftUp();
    });
    return this.size();
  }
  pop() {
    const poppedValue = this.peek();
    const bottom = this.size() - 1;
    if (bottom > top) {
      this._swap(top, bottom);
    }
    this._heap.pop();
    this._siftDown();
    return poppedValue;
  }
  replace(value) {
    const replacedValue = this.peek();
    this._heap[top] = value;
    this._siftDown();
    return replacedValue;
  }
  _greater(i, j) {
    return this._comparator(this._heap[i], this._heap[j]);
  }
  _swap(i, j) {
    const tmp = this._heap[i];
    this._heap[i] = this._heap[j];
    this._heap[j] = tmp;
  }
  _siftUp() {
    let node = this.size() - 1;
    while (node > top && this._greater(node, parent(node))) {
      this._swap(node, parent(node));
      node = parent(node);
    }
  }
  _siftDown() {
    let node = top;
    while (
      (left(node) < this.size() && this._greater(left(node), node)) ||
      (right(node) < this.size() && this._greater(right(node), node))
    ) {
      let maxChild =
        right(node) < this.size() && this._greater(right(node), left(node))
          ? right(node)
          : left(node);
      this._swap(node, maxChild);
      node = maxChild;
    }
  }
}

const GameMove = {
  UP: 1,
  DOWN: 2,
  RIGHT: 3,
  LEFT: 4,
  NOPE: 0,
};


let calls = 0;

const scoreFunction = (board) => {
  calls++;
  let score = 0;

  for (let i = 0; i < 4; i++) {
    for (let j = 0; j < 4; j++) {
      value = board.data[i * 4 + j];

      const desiredX = value === 0 ? 3 : (value - 1) % 4;
      const desiredY = value === 0 ? 3 : Math.floor((value - 1) / 4);

      // console.log(value, i, j, desiredX, desiredY);

      score += Math.abs(i - desiredY) + Math.abs(j - desiredX);
    }
  }

  return 2 * score;
};

class Board {
  constructor() {
    this.data = Array(16);
    this.reset();
  }

  reset() {
    for (let i = 0; i < 4; i++) {
      for (let j = 0; j < 4; j++) {
        this.data[i * 4 + j] = i * 4 + (j + 1);
      }
    }

    this.data[15] = 0;
    this.movesCount = 0;
    this.freeX = 3;
    this.freeY = 3;
  }

  isWin() {
    for (let i = 0; i < 15; i++) {
      if (this.data[i] !== i + 1) {
        return false;
      }
    }

    return this.data[15] === 0;
  }

  isLegalMove(move) {
    switch (move) {
      case GameMove.UP:
        if (this.freeY === 3) {
          return false;
        }
        break;
      case GameMove.DOWN:
        if (this.freeY === 0) {
          return false;
        }
        break;
      case GameMove.LEFT:
        if (this.freeX === 3) {
          return false;
        }
        break;
      case GameMove.RIGHT:
        if (this.freeX === 0) {
          return false;
        }
        break;
      default:
        return true;
    }
    return true;
  }

  applyMove(move) {
    if (!this.isLegalMove(move)) {
      throw new Error("Illegal Move");
    }

    switch (move) {
      case GameMove.UP:
        this.swap(this.freeY, this.freeX, this.freeY + 1, this.freeX);
        this.freeY++;
        break;
      case GameMove.DOWN:
        this.swap(this.freeY, this.freeX, this.freeY - 1, this.freeX);
        this.freeY--;
        break;
      case GameMove.LEFT:
        this.swap(this.freeY, this.freeX, this.freeY, this.freeX + 1);
        this.freeX++;
        break;
      case GameMove.RIGHT:
        this.swap(this.freeY, this.freeX, this.freeY, this.freeX - 1);
        this.freeX--;
        break;
    }
  }

  swap(y1, x1, y2, x2) {
    const i1 = y1 * 4 + x1;
    const i2 = y2 * 4 + x2;
    const tmp = this.data[i1];
    this.data[i1] = this.data[i2];
    this.data[i2] = tmp;
  }

  show() {
    for (let i = 0; i < 4; i++) {
      console.log(
        this.data[i * 4].toString().padStart(2, "0"),
        this.data[i * 4 + 1].toString().padStart(2, "0"),
        this.data[i * 4 + 2].toString().padStart(2, "0"),
        this.data[i * 4 + 3].toString().padStart(2, "0")
      );
    }
  }

  static getRandomBoard(numMoves) {
    const board = new Board();

    for (let i = 0; i < numMoves; i++) {
      const moveId = board.getRandomMove();

      board.applyMove(moveId);
    }

    return board;
  }

  getRandomMove() {
    let moveId;

    do {
      moveId = (Math.round(Math.random() * 4) + 1) % 5;
    } while (!this.isLegalMove(moveId));

    return moveId;
  }

  toString() {
    return this.data.map(toHexChar).join("")
  }

  fromString(str) {
    for (let i = 0; i < 16; i++) {
      this.data[i] = parseInt(str[i], 16);

      if (this.data[i] === 0) {
        this.freeX = i % 4;
        this.freeY = Math.floor(i / 4);
      }
    }

    this.movesCount = 0;
  }

  clone() {
    const newBoard = new Board();

    newBoard.data = [...this.data];
    newBoard.freeX = this.freeX;
    newBoard.freeY = this.freeY;
    newBoard.movesCount = this.movesCount;

    return newBoard;
  }
}

// Create new board

const opMovesArray = [
  { move: GameMove.UP, opMove: GameMove.DOWN },
  { move: GameMove.DOWN, opMove: GameMove.UP },
  { move: GameMove.RIGHT, opMove: GameMove.LEFT },
  { move: GameMove.LEFT, opMove: GameMove.RIGHT },
]

const opMove = {
  [GameMove.UP]: GameMove.DOWN,
  [GameMove.DOWN]: GameMove.UP,
  [GameMove.LEFT]: GameMove.RIGHT,
  [GameMove.RIGHT]: GameMove.LEFT,
}

const solve = (paramBoard) => {
  const board = paramBoard.clone();

  const queue = new PriorityQueue(
    (a, b) => a.score === b.score 
      ? a.steps < b.steps
      : a.score < b.score
    );
  const visited = new Map();
  let final;

  const startBoardStr = board.toString();

  queue.push({ 
    board: startBoardStr, 
    score: scoreFunction(board),
    steps: 0,
  });
  visited.set(startBoardStr, GameMove.NOPE);

  // let bestScore = scoreFunction(board);

  while (!queue.isEmpty()) {
    const queueEntry = queue.pop();
    const boardStr = queueEntry.board;
    board.fromString(boardStr);

    if (board.isWin()) {
      final = boardStr;
      break;
    }

    // if (calls % 100 === 0) {
    //   console.log('calls: ', calls, bestScore);
    // }

    for (const move of opMovesArray) {
      if (!board.isLegalMove(move.move)) {
        continue;
      }

      board.applyMove(move.move);
      const newBoardStr = board.toString();

      if (!visited.has(newBoardStr)) {
        const newScore = scoreFunction(board);
        // bestScore = Math.min(bestScore, newScore);

        queue.push({ 
          board: newBoardStr, 
          score: newScore + queueEntry.steps, 
          steps: queueEntry.steps + 1,
        });
        visited.set(newBoardStr, move.move);
      }

      board.applyMove(move.opMove);
    }
  }

  let moves = [];
  while (final !== startBoardStr) {
    const move = visited.get(final);

    moves.push(move);
    
    board.fromString(final);
    board.applyMove(opMove[move]);

    final = board.toString();
  }

  return moves.reverse();
};

const test = () => {
  const board = new Board();

  console.log("score1", scoreFunction(board));

  board.show();
  console.log(board.toString());

  board.applyMove(GameMove.DOWN);
  board.applyMove(GameMove.DOWN);
  board.applyMove(GameMove.DOWN);
  board.applyMove(GameMove.RIGHT);

  console.log("score2", scoreFunction(board));

  board.show();

  const randomBoard = Board.getRandomBoard(100);

  console.log("Random Board");
  randomBoard.show();
  console.log(randomBoard.toString());
  console.log("score3", scoreFunction(randomBoard));

  const boardFromStr = new Board();
  boardFromStr.fromString(randomBoard.toString());
  console.log("score4", scoreFunction(boardFromStr));
  boardFromStr.show();

  const result = solve(randomBoard);
  console.log(result);

  for (const move of result) {
    randomBoard.applyMove(move);
  }

  console.log("Random Board");
  randomBoard.show();
  console.log("Steps: ", result.length);
}

const getRandomBoard = () => {
  const randomBoard = Board.getRandomBoard(10000);

  randomBoard.show();

  console.log(randomBoard.toString());

  const solved = solve(randomBoard);

  console.log('solved', solved);

  return randomBoard;
}

const TEST1 = 'ECA91B5736D408F2';
const TEST2 = '59CE760134DF8B2A';

const solveBoardFromStr = (str) => {
  calls = 0;
  const board = new Board();
  board.fromString(str);

  performance.mark('start');
  const solved = solve(board);
  performance.mark('end');

  const measure = performance.measure('solve', 'start', 'end');

  // Log the measure
  console.log('duration: ', measure.duration.toFixed(2) + ' ms');
  console.log('steps: ', solved.length);
  console.log('calls: ', calls);

  return solved;
}
getRandomBoard();
solveBoardFromStr(TEST1);
solveBoardFromStr(TEST2);
