.PHONY: clean All

All:
	@echo "----------Building project:[ EpicQuest - Debug ]----------"
	@$(MAKE) -f  "EpicQuest.mk"
clean:
	@echo "----------Cleaning project:[ EpicQuest - Debug ]----------"
	@$(MAKE) -f  "EpicQuest.mk" clean
