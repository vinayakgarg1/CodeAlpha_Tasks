# Task 4: OOP-Based Banking System

An interactive console application developed in C++ that simulates fundamental retail banking operations. This project serves as a practical demonstration of Object-Oriented Programming (OOP) concepts such as encapsulation, data abstraction, modular system architecture, and dynamic memory collection.

---

## 💎 Project Objectives & Core Requirements

As outlined in the internship blueprint, this system satisfies the following technical mandates:
* **Object-Oriented Design:** Establishes standalone decoupled entities using custom classes to govern `Customer`, `Account`, and `Transaction` scopes natively.
* **Account Lifecycle Management:** Provisions functional boundaries allowing secure onboarding of customer profiles linked directly with structured financial ledger units.
* **Financial Operation Pipeline:** Features execution modules verifying balance thresholds prior to concluding Deposits, Withdrawals, and Inter-Account Bank Transfers.
* **Comprehensive Audit Trail:** Captures real-time immutable vector registries tracking financial movements to output dynamic, structured transaction history records on-demand.

---

## 🛠️ System Architecture

The core program maps its operations cleanly across three central object models:

### 1. `Transaction` Struct
* Represents individual ledger rows securely.
* Holds structural properties tracking the nature of movement (`Type`), capital flux (`Amount`), and post-execution balance states (`ResultingBalance`).

### 2. `Account` Class
* Encapsulates financial states securely behind `private` visibility fields to safeguard internal state properties against unauthorized outside modification.
* Exposes standard public interfaces enabling operational tracking (`deposit`, `withdraw`, `recordTransfer`).
* Maintains an expanding vector timeline log representing the individual account's unique historical trail.

### 3. `Customer` Class
* Maps a real-world client entity directly to a distinct financial account via composition.
* Aggregates standard personal markers tracking individual client Names, System IDs, and Account Reference units.

---

## 🚀 Menu Interface Features

Upon launch, users interact with a persistent menu panel offering the following capabilities:
1. **Create New Account:** Registers a new client profile, automatically allocates unique incrementing IDs, and provisions a brand new account number (starting at 1001).
2. **Deposit Funds:** Validates the presence of the account record and adds positive values directly to the balance.
3. **Withdraw Funds:** Verifies against insufficient fund restrictions before deducting capital from the balance.
4. **Transfer Funds:** Connects two unique account instances, safely verifying and shifting balances between the sender and receiver logs simultaneously.
5. **View Account Details & History:** Discharges complete profile summaries along with a clean tabular chart displaying every previous transaction.

---