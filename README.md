# Leistungsstarkes Game Framework

LGF (Leistungsstarkes Game Framework) 是一款基於陳偉凱老師的 Game Framework 加上些許功能的 Powerful Game Framework。

專案不保證長期維護，有任何問題或者任何其他想要的 feature，請丟 issue，祝使用愉快 :D



## Installation

1. 將此專案 clone 下來

## Add

2023.3.4
增加暫時操作操作用的手柄

目前問題 : 

1. init畫面完會黑屏，要在點一下視窗才能開始遊戲 
2. 座標都是大概位置，全部都要微調，不過運算式應該還好
3. 鼠標、操作柄、人物移動(就是背景移動)的關係 : 

使用OnMouseMove (Unit nFlags,Cpoint point)

point -> 鼠標物件，可以得到鼠標作標

nFlags -> 不清楚，預測應該是判斷鼠標是否被點擊

當在視窗中拖曳鼠標時，會讓操作柄出現小範圍移動(不超出特定範圍)，當操作柄移動後，於show_img裡先判斷操作柄偏離原位距離，計算後乘上倍率並反向(人物向上跑 == 背景向下移動)，實現移動

(紅框目前景為輔助縣)

p.s 人物目前可使用鍵盤調整在視窗中的位置，我想說這樣比較好調整之後的座標

