/* ************************************************************************** */
/**

  @File Name
    card.c

  @Description
    This file implements the functionality for generating random cards
    within the casino game. It includes the definition of the Card struct,
    which represents a playing card with attributes for value and suit.
    The main purpose of this module is to provide a mechanism for generating
    random cards that can be used in various aspects of the casino game,
    such as dealing cards to players and managing the game's card deck.

  @Author
    Trevor Arcieri and Nicholas Chown

 */
/* ************************************************************************** */

#include "cards.h"

void initCardSet(CardSet* cardSet, int numDecks, double shoeRatio)
{
    cardSet->numDecks = numDecks;
    cardSet->shoeRatio = shoeRatio;
    cardSet->cardsLeft = numDecks * 52; // Each deck has 52 cards
}

void initCardsInSet(CardSet* cardSet)
{
    // Initialize the deck and discard pile
    for (int deck = 0; deck < cardSet->numDecks; ++deck)
    {
        for (int value = ACE; value <= KING; ++value)
        {
            for (int suit = HEARTS; suit <= SPADES; ++suit)
            {
                cardSet->deck[deck * 52 + (value - ACE) * 4 + suit].value = (CardValue)value;
                cardSet->deck[deck * 52 + (value - ACE) * 4 + suit].suit = (Suit)suit;
            }
        }
    }

    shuffleCardSet(cardSet);
}

void pullTopCard(Card *topCard, CardSet *cardSet, ShuffleStatus *shuffleStatus)
{
    // Check if shuffle is needed
    if ((double)cardSet->cardsLeft / (double)(cardSet->numDecks * 52) <= cardSet->shoeRatio)
    {
        shuffleCardSet(cardSet);
        *shuffleStatus = SHUFFLING;
    }
    else
    {
        *shuffleStatus = NO_SHUFFLE;
    }

    // Pull the top card
    *topCard = cardSet->deck[--cardSet->cardsLeft];

    // Move the pulled card to the discard pile
    cardSet->discardPile[cardSet->cardsLeft] = *topCard;
}

void discardTopCard(CardSet *cardSet)
{
    // Move the top card to the discard pile
    cardSet->discardPile[--cardSet->cardsLeft] = cardSet->deck[cardSet->cardsLeft];
}

void shuffleCardSet(CardSet *cardSet)
{
    // Combine the discard pile and the remaining deck
    int totalCards = cardSet->numDecks * 52;
    Card combinedDeck[totalCards];

    // Copy remaining deck to the combined deck
    for (int i = 0; i < cardSet->cardsLeft; ++i)
    {
        combinedDeck[i] = cardSet->deck[i];
    }

    // Copy discard pile to the combined deck
    for (int i = 0; i < totalCards - cardSet->cardsLeft; ++i)
    {
        combinedDeck[cardSet->cardsLeft + i] = cardSet->discardPile[totalCards - i - 1];
    }

    // Shuffle the combined deck
    for (int i = totalCards - 1; i > 0; --i)
    {
        int j = generateRandomNumber(0, i + 1);
        // Swap
        Card temp = combinedDeck[i];
        combinedDeck[i] = combinedDeck[j];
        combinedDeck[j] = temp;
    }

    // Copy the shuffled combined deck back to the main deck
    for (int i = 0; i < totalCards; ++i)
    {
        cardSet->deck[i] = combinedDeck[i];
    }

    // Reset cards left and free the temporary combined deck
    cardSet->cardsLeft = totalCards;
}
