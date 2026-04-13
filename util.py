import torch

def tokenize_equation(equation): #returns the equation made up of tokens
    return equation.strip().split()

def encode_equation(equation, maxLen, tokenToIndex): #takes an equation and tokenizes it as well as prepping it
    tokens = tokenize_equation(equation)
    tokens = tokens[:maxLen]

    indices = [tokenToIndex.get(tok, tokenToIndex["<PAD>"]) for tok in tokens]

    indices += [tokenToIndex["<PAD>"]] * (maxLen - len(indices))
    return torch.tensor(indices, dtype=torch.long)

def predict(equation, model, std, mean, maxLen, tokenToIndex): #get models answer to asked equation
    x = encode_equation(equation, maxLen, tokenToIndex).unsqueeze(0)

    with torch.no_grad():
        output = model(x).item()

    output = output * std + mean #denormalize
    return output