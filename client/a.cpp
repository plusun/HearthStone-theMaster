

{
	while (1)
	{
		vector<int> vi = _client.opponent_turn();
		switch (vi[0])
		{
			case 6:
				if (vi[1] == '1')
					;//TODO: you lose
				else
				if (vi[1] == '2')
					;//TODO: you win
				else
					;//TODO: draw
				break;
			case 4:
				//TODO: player2.endturn();
				break;
			case 1:
				int _card_position = vi[1];
				int _position = vi[2];
				int _side = vi[3];
				int _target = vi[4];
				//TODO: player2.use(_card_position, _position, _side, _target);
				break;
			case 2:
				int _minion1 = vi[1];
				int _minion2 = vi[2];
				//TODO: battlefield[1][_minion2] attack battlefield[0][_minion1];
				break;
			case 8:
				int _card = vi[1];
				//TODO: player2.handcard.draw(_card);
				break;
			default:
				//TODO: error,should never reach here
		}

	}


}