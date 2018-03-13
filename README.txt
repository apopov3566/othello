Alex: Wrote/improved the heuristic function (implemented stability checking, positioning checking,
various bugfixes), improved minimax to make it n-depth, wrote time-to-minimax-depth calculation code.

Angelina: Improved heuristic function (implemented mobility checking), wrote minimax code.

Improvements to the AI:
 - Comprehensive heuristic accounting for stability, positioning, mobility, and number of tiles.
 - n-depth minimax of heuristic.
 - time-dependent minimax depth selection (attempts to use all time available to the bot).
Although this is a relatively standard strategy, the comprehensive nature of the heuristic combined
with the ability to use large-depth minimax when required will hopefuly result in a good score.
